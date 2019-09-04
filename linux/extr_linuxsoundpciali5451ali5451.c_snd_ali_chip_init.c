#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_ali {scalar_t__ revision; int spdif_mask; int num_of_codecs; TYPE_1__* card; scalar_t__ spdif_support; void* ac97_ext_status; void* ac97_ext_id; int /*<<< orphan*/  pci; struct pci_dev* pci_m7101; struct pci_dev* pci_m1533; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_ID ; 
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
 scalar_t__ ALI_5451_V02 ; 
 int /*<<< orphan*/  ALI_AINT ; 
 int /*<<< orphan*/  ALI_AINTEN ; 
 int /*<<< orphan*/  ALI_GLOBAL_CONTROL ; 
 int /*<<< orphan*/  ALI_MPUR2 ; 
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ALI_SCTRL ; 
 int ALI_SCTRL_CODEC2_READY ; 
 int ALI_SCTRL_GPIO_IN2 ; 
 int ALI_SCTRL_LINE_IN2 ; 
 int ALI_SCTRL_LINE_OUT_EN ; 
 int /*<<< orphan*/  ALI_VOLUME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,unsigned int) ; 
 void* snd_ali_codec_peek (struct snd_ali*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_enable_spdif_out (struct snd_ali*) ; 
 scalar_t__ snd_ali_reset_5451 (struct snd_ali*) ; 

__attribute__((used)) static int snd_ali_chip_init(struct snd_ali *codec)
{
	unsigned int legacy;
	unsigned char temp;
	struct pci_dev *pci_dev;

	dev_dbg(codec->card->dev, "chip initializing ...\n");

	if (snd_ali_reset_5451(codec)) {
		dev_err(codec->card->dev, "ali_chip_init: reset 5451 error.\n");
		return -1;
	}

	if (codec->revision == ALI_5451_V02) {
        	pci_dev = codec->pci_m1533;
		pci_read_config_byte(pci_dev, 0x59, &temp);
		temp |= 0x80;
		pci_write_config_byte(pci_dev, 0x59, temp);
	
		pci_dev = codec->pci_m7101;
		pci_read_config_byte(pci_dev, 0xb8, &temp);
		temp |= 0x20;
		pci_write_config_byte(pci_dev, 0xB8, temp);
	}

	pci_read_config_dword(codec->pci, 0x44, &legacy);
	legacy &= 0xff00ff00;
	legacy |= 0x000800aa;
	pci_write_config_dword(codec->pci, 0x44, legacy);

	outl(0x80000001, ALI_REG(codec, ALI_GLOBAL_CONTROL));
	outl(0x00000000, ALI_REG(codec, ALI_AINTEN));
	outl(0xffffffff, ALI_REG(codec, ALI_AINT));
	outl(0x00000000, ALI_REG(codec, ALI_VOLUME));
	outb(0x10, 	 ALI_REG(codec, ALI_MPUR2));

	codec->ac97_ext_id = snd_ali_codec_peek(codec, 0, AC97_EXTENDED_ID);
	codec->ac97_ext_status = snd_ali_codec_peek(codec, 0,
						    AC97_EXTENDED_STATUS);
	if (codec->spdif_support) {
		snd_ali_enable_spdif_out(codec);
		codec->spdif_mask = 0x00000002;
	}

	codec->num_of_codecs = 1;

	/* secondary codec - modem */
	if (inl(ALI_REG(codec, ALI_SCTRL)) & ALI_SCTRL_CODEC2_READY) {
		codec->num_of_codecs++;
		outl(inl(ALI_REG(codec, ALI_SCTRL)) |
		     (ALI_SCTRL_LINE_IN2 | ALI_SCTRL_GPIO_IN2 |
		      ALI_SCTRL_LINE_OUT_EN),
		     ALI_REG(codec, ALI_SCTRL));
	}

	dev_dbg(codec->card->dev, "chip initialize succeed.\n");
	return 0;

}