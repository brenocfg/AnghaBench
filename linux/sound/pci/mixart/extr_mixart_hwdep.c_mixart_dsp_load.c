#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_mixart {int /*<<< orphan*/  card; int /*<<< orphan*/  mgr; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct mixart_mgr {int board_type; int num_cards; TYPE_2__* pci; struct snd_mixart** chip; TYPE_1__ flowinfo; } ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DAUGHTER_TYPE_MASK ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
#define  MIXART_AESEBUBOARD_XLX_INDEX 130 
 int MIXART_DAUGHTER_TYPE_AES ; 
 int MIXART_DAUGHTER_TYPE_NONE ; 
 int MIXART_FLOWTABLE_PTR ; 
 int /*<<< orphan*/  MIXART_MEM (struct mixart_mgr*,int) ; 
#define  MIXART_MOTHERBOARD_ELF_INDEX 129 
 int MIXART_MOTHERBOARD_XLX_BASE_ADDRESS ; 
#define  MIXART_MOTHERBOARD_XLX_INDEX 128 
 int MIXART_PSEUDOREG_BOARDNUMBER ; 
 int MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET ; 
 int MIXART_PSEUDOREG_DBRD_TYPE_OFFSET ; 
 int MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET ; 
 int MIXART_PSEUDOREG_DXLX_SIZE_OFFSET ; 
 int MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ; 
 int MIXART_PSEUDOREG_ELF_STATUS_OFFSET ; 
 int MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET ; 
 int MIXART_PSEUDOREG_MXLX_SIZE_OFFSET ; 
 int MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int mixart_first_init (struct mixart_mgr*) ; 
 int mixart_load_elf (struct mixart_mgr*,struct firmware const*) ; 
 int mixart_wait_nice_for_register_value (struct mixart_mgr*,int,int,int,int) ; 
 int readl_be (int /*<<< orphan*/ ) ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int snd_mixart_create_mixer (int /*<<< orphan*/ ) ; 
 int snd_mixart_create_pcm (struct snd_mixart*) ; 
 int /*<<< orphan*/  snd_mixart_init_mailbox (struct mixart_mgr*) ; 
 int /*<<< orphan*/  writel_be (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixart_dsp_load(struct mixart_mgr* mgr, int index, const struct firmware *dsp)
{
	int           err, card_index;
	u32           status_xilinx, status_elf, status_daught;
	u32           val;

	/* read motherboard xilinx status */
	status_xilinx = readl_be( MIXART_MEM( mgr,MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ));
	/* read elf status */
	status_elf = readl_be( MIXART_MEM( mgr,MIXART_PSEUDOREG_ELF_STATUS_OFFSET ));
	/* read daughterboard xilinx status */
	status_daught = readl_be( MIXART_MEM( mgr,MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ));

	/* motherboard xilinx status 5 will say that the board is performing a reset */
	if (status_xilinx == 5) {
		dev_err(&mgr->pci->dev, "miXart is resetting !\n");
		return -EAGAIN; /* try again later */
	}

	switch (index)   {
	case MIXART_MOTHERBOARD_XLX_INDEX:

		/* xilinx already loaded ? */ 
		if (status_xilinx == 4) {
			dev_dbg(&mgr->pci->dev, "xilinx is already loaded !\n");
			return 0;
		}
		/* the status should be 0 == "idle" */
		if (status_xilinx != 0) {
			dev_err(&mgr->pci->dev,
				"xilinx load error ! status = %d\n",
				   status_xilinx);
			return -EIO; /* modprob -r may help ? */
		}

		/* check xilinx validity */
		if (((u32*)(dsp->data))[0] == 0xffffffff)
			return -EINVAL;
		if (dsp->size % 4)
			return -EINVAL;

		/* set xilinx status to copying */
		writel_be( 1, MIXART_MEM( mgr, MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ));

		/* setup xilinx base address */
		writel_be( MIXART_MOTHERBOARD_XLX_BASE_ADDRESS, MIXART_MEM( mgr,MIXART_PSEUDOREG_MXLX_BASE_ADDR_OFFSET ));
		/* setup code size for xilinx file */
		writel_be( dsp->size, MIXART_MEM( mgr, MIXART_PSEUDOREG_MXLX_SIZE_OFFSET ));

		/* copy xilinx code */
		memcpy_toio(  MIXART_MEM( mgr, MIXART_MOTHERBOARD_XLX_BASE_ADDRESS),  dsp->data,  dsp->size);
    
		/* set xilinx status to copy finished */
		writel_be( 2, MIXART_MEM( mgr, MIXART_PSEUDOREG_MXLX_STATUS_OFFSET ));

		/* return, because no further processing needed */
		return 0;

	case MIXART_MOTHERBOARD_ELF_INDEX:

		if (status_elf == 4) {
			dev_dbg(&mgr->pci->dev, "elf file already loaded !\n");
			return 0;
		}

		/* the status should be 0 == "idle" */
		if (status_elf != 0) {
			dev_err(&mgr->pci->dev,
				"elf load error ! status = %d\n",
				   status_elf);
			return -EIO; /* modprob -r may help ? */
		}

		/* wait for xilinx status == 4 */
		err = mixart_wait_nice_for_register_value( mgr, MIXART_PSEUDOREG_MXLX_STATUS_OFFSET, 1, 4, 500); /* 5sec */
		if (err < 0) {
			dev_err(&mgr->pci->dev, "xilinx was not loaded or "
				   "could not be started\n");
			return err;
		}

		/* init some data on the card */
		writel_be( 0, MIXART_MEM( mgr, MIXART_PSEUDOREG_BOARDNUMBER ) ); /* set miXart boardnumber to 0 */
		writel_be( 0, MIXART_MEM( mgr, MIXART_FLOWTABLE_PTR ) );         /* reset pointer to flow table on miXart */

		/* set elf status to copying */
		writel_be( 1, MIXART_MEM( mgr, MIXART_PSEUDOREG_ELF_STATUS_OFFSET ));

		/* process the copying of the elf packets */
		err = mixart_load_elf( mgr, dsp );
		if (err < 0) return err;

		/* set elf status to copy finished */
		writel_be( 2, MIXART_MEM( mgr, MIXART_PSEUDOREG_ELF_STATUS_OFFSET ));

		/* wait for elf status == 4 */
		err = mixart_wait_nice_for_register_value( mgr, MIXART_PSEUDOREG_ELF_STATUS_OFFSET, 1, 4, 300); /* 3sec */
		if (err < 0) {
			dev_err(&mgr->pci->dev, "elf could not be started\n");
			return err;
		}

		/* miXart waits at this point on the pointer to the flow table */
		writel_be( (u32)mgr->flowinfo.addr, MIXART_MEM( mgr, MIXART_FLOWTABLE_PTR ) ); /* give pointer of flow table to miXart */

		return 0;  /* return, another xilinx file has to be loaded before */

	case MIXART_AESEBUBOARD_XLX_INDEX:
	default:

		/* elf and xilinx should be loaded */
		if (status_elf != 4 || status_xilinx != 4) {
			dev_err(&mgr->pci->dev, "xilinx or elf not "
			       "successfully loaded\n");
			return -EIO; /* modprob -r may help ? */
		}

		/* wait for daughter detection != 0 */
		err = mixart_wait_nice_for_register_value( mgr, MIXART_PSEUDOREG_DBRD_PRESENCE_OFFSET, 0, 0, 30); /* 300msec */
		if (err < 0) {
			dev_err(&mgr->pci->dev, "error starting elf file\n");
			return err;
		}

		/* the board type can now be retrieved */
		mgr->board_type = (DAUGHTER_TYPE_MASK & readl_be( MIXART_MEM( mgr, MIXART_PSEUDOREG_DBRD_TYPE_OFFSET)));

		if (mgr->board_type == MIXART_DAUGHTER_TYPE_NONE)
			break;  /* no daughter board; the file does not have to be loaded, continue after the switch */

		/* only if aesebu daughter board presence (elf code must run)  */ 
		if (mgr->board_type != MIXART_DAUGHTER_TYPE_AES )
			return -EINVAL;

		/* daughter should be idle */
		if (status_daught != 0) {
			dev_err(&mgr->pci->dev,
				"daughter load error ! status = %d\n",
			       status_daught);
			return -EIO; /* modprob -r may help ? */
		}
 
		/* check daughterboard xilinx validity */
		if (((u32*)(dsp->data))[0] == 0xffffffff)
			return -EINVAL;
		if (dsp->size % 4)
			return -EINVAL;

		/* inform mixart about the size of the file */
		writel_be( dsp->size, MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_SIZE_OFFSET ));

		/* set daughterboard status to 1 */
		writel_be( 1, MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ));

		/* wait for status == 2 */
		err = mixart_wait_nice_for_register_value( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET, 1, 2, 30); /* 300msec */
		if (err < 0) {
			dev_err(&mgr->pci->dev, "daughter board load error\n");
			return err;
		}

		/* get the address where to write the file */
		val = readl_be( MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_BASE_ADDR_OFFSET ));
		if (!val)
			return -EINVAL;

		/* copy daughterboard xilinx code */
		memcpy_toio(  MIXART_MEM( mgr, val),  dsp->data,  dsp->size);

		/* set daughterboard status to 4 */
		writel_be( 4, MIXART_MEM( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET ));

		/* continue with init */
		break;
	} /* end of switch file index*/

        /* wait for daughter status == 3 */
        err = mixart_wait_nice_for_register_value( mgr, MIXART_PSEUDOREG_DXLX_STATUS_OFFSET, 1, 3, 300); /* 3sec */
        if (err < 0) {
		dev_err(&mgr->pci->dev,
			   "daughter board could not be initialised\n");
		return err;
	}

	/* init mailbox (communication with embedded) */
	snd_mixart_init_mailbox(mgr);

	/* first communication with embedded */
	err = mixart_first_init(mgr);
        if (err < 0) {
		dev_err(&mgr->pci->dev, "miXart could not be set up\n");
		return err;
	}

       	/* create devices and mixer in accordance with HW options*/
        for (card_index = 0; card_index < mgr->num_cards; card_index++) {
		struct snd_mixart *chip = mgr->chip[card_index];

		if ((err = snd_mixart_create_pcm(chip)) < 0)
			return err;

		if (card_index == 0) {
			if ((err = snd_mixart_create_mixer(chip->mgr)) < 0)
	        		return err;
		}

		if ((err = snd_card_register(chip->card)) < 0)
			return err;
	}

	dev_dbg(&mgr->pci->dev,
		"miXart firmware downloaded and successfully set up\n");

	return 0;
}