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
struct snd_pcxhr {int /*<<< orphan*/  card; int /*<<< orphan*/  mgr; } ;
struct pcxhr_mgr {int num_cards; TYPE_1__* pci; struct snd_pcxhr** chip; } ;
struct firmware {int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
#define  PCXHR_FIRMWARE_DSP_BOOT_INDEX 132 
#define  PCXHR_FIRMWARE_DSP_EPRM_INDEX 131 
#define  PCXHR_FIRMWARE_DSP_MAIN_INDEX 130 
#define  PCXHR_FIRMWARE_XLX_COM_INDEX 129 
#define  PCXHR_FIRMWARE_XLX_INT_INDEX 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pcxhr_config_pipes (struct pcxhr_mgr*) ; 
 int pcxhr_create_mixer (int /*<<< orphan*/ ) ; 
 int pcxhr_create_pcm (struct snd_pcxhr*) ; 
 int pcxhr_init_board (struct pcxhr_mgr*) ; 
 int pcxhr_load_boot_binary (struct pcxhr_mgr*,struct firmware const*) ; 
 int pcxhr_load_dsp_binary (struct pcxhr_mgr*,struct firmware const*) ; 
 int pcxhr_load_eeprom_binary (struct pcxhr_mgr*,struct firmware const*) ; 
 int pcxhr_load_xilinx_binary (struct pcxhr_mgr*,struct firmware const*,int) ; 
 int /*<<< orphan*/  pcxhr_reset_dsp (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pcxhr_reset_xilinx_com (struct pcxhr_mgr*) ; 
 int pcxhr_start_pipes (struct pcxhr_mgr*) ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcxhr_dsp_load(struct pcxhr_mgr *mgr, int index,
			  const struct firmware *dsp)
{
	int err, card_index;

	dev_dbg(&mgr->pci->dev,
		"loading dsp [%d] size = %zd\n", index, dsp->size);

	switch (index) {
	case PCXHR_FIRMWARE_XLX_INT_INDEX:
		pcxhr_reset_xilinx_com(mgr);
		return pcxhr_load_xilinx_binary(mgr, dsp, 0);

	case PCXHR_FIRMWARE_XLX_COM_INDEX:
		pcxhr_reset_xilinx_com(mgr);
		return pcxhr_load_xilinx_binary(mgr, dsp, 1);

	case PCXHR_FIRMWARE_DSP_EPRM_INDEX:
		pcxhr_reset_dsp(mgr);
		return pcxhr_load_eeprom_binary(mgr, dsp);

	case PCXHR_FIRMWARE_DSP_BOOT_INDEX:
		return pcxhr_load_boot_binary(mgr, dsp);

	case PCXHR_FIRMWARE_DSP_MAIN_INDEX:
		err = pcxhr_load_dsp_binary(mgr, dsp);
		if (err)
			return err;
		break;	/* continue with first init */
	default:
		dev_err(&mgr->pci->dev, "wrong file index\n");
		return -EFAULT;
	} /* end of switch file index*/

	/* first communication with embedded */
	err = pcxhr_init_board(mgr);
        if (err < 0) {
		dev_err(&mgr->pci->dev, "pcxhr could not be set up\n");
		return err;
	}
	err = pcxhr_config_pipes(mgr);
        if (err < 0) {
		dev_err(&mgr->pci->dev, "pcxhr pipes could not be set up\n");
		return err;
	}
       	/* create devices and mixer in accordance with HW options*/
        for (card_index = 0; card_index < mgr->num_cards; card_index++) {
		struct snd_pcxhr *chip = mgr->chip[card_index];

		if ((err = pcxhr_create_pcm(chip)) < 0)
			return err;

		if (card_index == 0) {
			if ((err = pcxhr_create_mixer(chip->mgr)) < 0)
				return err;
		}
		if ((err = snd_card_register(chip->card)) < 0)
			return err;
	}
	err = pcxhr_start_pipes(mgr);
        if (err < 0) {
		dev_err(&mgr->pci->dev, "pcxhr pipes could not be started\n");
		return err;
	}
	dev_dbg(&mgr->pci->dev,
		"pcxhr firmware downloaded and successfully set up\n");

	return 0;
}