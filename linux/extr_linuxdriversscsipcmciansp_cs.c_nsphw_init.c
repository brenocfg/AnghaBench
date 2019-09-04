#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int BaseAddress; int ScsiClockDiv; int TransferMode; scalar_t__ FifoCount; int /*<<< orphan*/ * CurrentSC; } ;
typedef  TYPE_1__ nsp_hw_data ;

/* Variables and functions */
 int /*<<< orphan*/  ACKWIDTH ; 
 int ACK_COUNTER_CLEAR ; 
 int /*<<< orphan*/  CLOCKDIV ; 
 int CLOCK_40M ; 
 int /*<<< orphan*/  FALSE ; 
 int FAST_20 ; 
 int HOST_COUNTER_CLEAR ; 
 int /*<<< orphan*/  IFSELECT ; 
 int /*<<< orphan*/  IF_IFSEL ; 
 int /*<<< orphan*/  IF_REGSEL ; 
 int /*<<< orphan*/  IRQCONTROL ; 
 int /*<<< orphan*/  IRQCONTROL_ALLCLEAR ; 
 int /*<<< orphan*/  IRQCONTROL_ALLMASK ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MODE_IO8 ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 int /*<<< orphan*/  OTHERCONTROL ; 
 int /*<<< orphan*/  PARITYCTRL ; 
 int /*<<< orphan*/  POINTERCLR ; 
 int POINTER_CLEAR ; 
 int POWER_ON ; 
 int REQ_COUNTER_CLEAR ; 
 int RESELECT_EI ; 
 int /*<<< orphan*/  SCSIIRQMODE ; 
 int SCSI_PHASE_CHANGE_EI ; 
 int SCSI_RESET_IRQ_EI ; 
 int /*<<< orphan*/  SYNCREG ; 
 int /*<<< orphan*/  TERMPWRCTRL ; 
 int /*<<< orphan*/  TIMERCOUNT ; 
 int TPWR_SENSE ; 
 int /*<<< orphan*/  TRANSFERMODE ; 
 int TRUE ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsp_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp_setup_fifo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_write (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsphw_init_sync (TYPE_1__*) ; 

__attribute__((used)) static int nsphw_init(nsp_hw_data *data)
{
	unsigned int base     = data->BaseAddress;

	nsp_dbg(NSP_DEBUG_INIT, "in base=0x%x", base);

	data->ScsiClockDiv = CLOCK_40M | FAST_20;
	data->CurrentSC    = NULL;
	data->FifoCount    = 0;
	data->TransferMode = MODE_IO8;

	nsphw_init_sync(data);

	/* block all interrupts */
	nsp_write(base,	      IRQCONTROL,   IRQCONTROL_ALLMASK);

	/* setup SCSI interface */
	nsp_write(base,	      IFSELECT,	    IF_IFSEL);

	nsp_index_write(base, SCSIIRQMODE,  0);

	nsp_index_write(base, TRANSFERMODE, MODE_IO8);
	nsp_index_write(base, CLOCKDIV,	    data->ScsiClockDiv);

	nsp_index_write(base, PARITYCTRL,   0);
	nsp_index_write(base, POINTERCLR,   POINTER_CLEAR     |
					    ACK_COUNTER_CLEAR |
					    REQ_COUNTER_CLEAR |
					    HOST_COUNTER_CLEAR);

	/* setup fifo asic */
	nsp_write(base,	      IFSELECT,	    IF_REGSEL);
	nsp_index_write(base, TERMPWRCTRL,  0);
	if ((nsp_index_read(base, OTHERCONTROL) & TPWR_SENSE) == 0) {
		nsp_msg(KERN_INFO, "terminator power on");
		nsp_index_write(base, TERMPWRCTRL, POWER_ON);
	}

	nsp_index_write(base, TIMERCOUNT,   0);
	nsp_index_write(base, TIMERCOUNT,   0); /* requires 2 times!! */

	nsp_index_write(base, SYNCREG,	    0);
	nsp_index_write(base, ACKWIDTH,	    0);

	/* enable interrupts and ack them */
	nsp_index_write(base, SCSIIRQMODE,  SCSI_PHASE_CHANGE_EI |
					    RESELECT_EI		 |
					    SCSI_RESET_IRQ_EI	 );
	nsp_write(base,	      IRQCONTROL,   IRQCONTROL_ALLCLEAR);

	nsp_setup_fifo(data, FALSE);

	return TRUE;
}