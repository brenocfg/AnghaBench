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
typedef  int u8 ;
typedef  int u16 ;
struct snd_ali {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_REG (struct snd_ali*,scalar_t__) ; 
 scalar_t__ ALI_SPDIF_CS ; 
 scalar_t__ ALI_SPDIF_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ali_delay (struct snd_ali*,int) ; 

__attribute__((used)) static void snd_ali_detect_spdif_rate(struct snd_ali *codec)
{
	u16 wval;
	u16 count = 0;
	u8  bval, R1 = 0, R2;

	bval  = inb(ALI_REG(codec, ALI_SPDIF_CTRL + 1));
	bval |= 0x1F;
	outb(bval, ALI_REG(codec, ALI_SPDIF_CTRL + 1));

	while ((R1 < 0x0b || R1 > 0x0e) && R1 != 0x12 && count <= 50000) {
		count ++;
		snd_ali_delay(codec, 6);
		bval = inb(ALI_REG(codec, ALI_SPDIF_CTRL + 1));
		R1 = bval & 0x1F;
	}

	if (count > 50000) {
		dev_err(codec->card->dev, "ali_detect_spdif_rate: timeout!\n");
		return;
	}

	for (count = 0; count <= 50000; count++) {
		snd_ali_delay(codec, 6);
		bval = inb(ALI_REG(codec,ALI_SPDIF_CTRL + 1));
		R2 = bval & 0x1F;
		if (R2 != R1)
			R1 = R2;
		else
			break;
	}

	if (count > 50000) {
		dev_err(codec->card->dev, "ali_detect_spdif_rate: timeout!\n");
		return;
	}

	if (R2 >= 0x0b && R2 <= 0x0e) {
		wval  = inw(ALI_REG(codec, ALI_SPDIF_CTRL + 2));
		wval &= 0xe0f0;
		wval |= (0x09 << 8) | 0x05;
		outw(wval, ALI_REG(codec, ALI_SPDIF_CTRL + 2));

		bval  = inb(ALI_REG(codec, ALI_SPDIF_CS + 3)) & 0xf0;
		outb(bval | 0x02, ALI_REG(codec, ALI_SPDIF_CS + 3));
	} else if (R2 == 0x12) {
		wval  = inw(ALI_REG(codec, ALI_SPDIF_CTRL + 2));
		wval &= 0xe0f0;
		wval |= (0x0e << 8) | 0x08;
		outw(wval, ALI_REG(codec, ALI_SPDIF_CTRL + 2));

		bval  = inb(ALI_REG(codec,ALI_SPDIF_CS + 3)) & 0xf0;
		outb(bval | 0x03, ALI_REG(codec, ALI_SPDIF_CS + 3));
	}
}