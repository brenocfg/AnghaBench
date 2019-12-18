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
typedef  int u32 ;
struct pcxhr_rmh {int* stat; int* cmd; int stat_len; } ;
struct pcxhr_mgr {int src_it_dsp; TYPE_1__* pci; struct pcxhr_rmh* prmh; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ASYNC ; 
 int /*<<< orphan*/  CMD_TEST_IT ; 
 int FIELD_SIZE ; 
 int MASK_FIRST_FIELD ; 
 int /*<<< orphan*/  PCXHR_ERR_AUDIO ; 
 int /*<<< orphan*/  PCXHR_ERR_PIPE ; 
 int /*<<< orphan*/  PCXHR_ERR_STREAM ; 
 int PCXHR_IRQ_ASYNC ; 
 int PCXHR_IRQ_FREQ_CHANGE ; 
 int PCXHR_IRQ_NOTIFY ; 
 int PCXHR_IRQ_TIME_CODE ; 
 int PCXHR_SIZE_MAX_LONG_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pcxhr_handle_async_err (struct pcxhr_mgr*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 

__attribute__((used)) static void pcxhr_msg_thread(struct pcxhr_mgr *mgr)
{
	struct pcxhr_rmh *prmh = mgr->prmh;
	int err;
	int i, j;

	if (mgr->src_it_dsp & PCXHR_IRQ_FREQ_CHANGE)
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_FREQ_CHANGE event occurred\n");
	if (mgr->src_it_dsp & PCXHR_IRQ_TIME_CODE)
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_TIME_CODE event occurred\n");
	if (mgr->src_it_dsp & PCXHR_IRQ_NOTIFY)
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_NOTIFY event occurred\n");
	if (mgr->src_it_dsp & (PCXHR_IRQ_FREQ_CHANGE | PCXHR_IRQ_TIME_CODE)) {
		/* clear events FREQ_CHANGE and TIME_CODE */
		pcxhr_init_rmh(prmh, CMD_TEST_IT);
		err = pcxhr_send_msg(mgr, prmh);
		dev_dbg(&mgr->pci->dev, "CMD_TEST_IT : err=%x, stat=%x\n",
			    err, prmh->stat[0]);
	}
	if (mgr->src_it_dsp & PCXHR_IRQ_ASYNC) {
		dev_dbg(&mgr->pci->dev,
			"PCXHR_IRQ_ASYNC event occurred\n");

		pcxhr_init_rmh(prmh, CMD_ASYNC);
		prmh->cmd[0] |= 1;	/* add SEL_ASYNC_EVENTS */
		/* this is the only one extra long response command */
		prmh->stat_len = PCXHR_SIZE_MAX_LONG_STATUS;
		err = pcxhr_send_msg(mgr, prmh);
		if (err)
			dev_err(&mgr->pci->dev, "ERROR pcxhr_msg_thread=%x;\n",
				   err);
		i = 1;
		while (i < prmh->stat_len) {
			int nb_audio = ((prmh->stat[i] >> FIELD_SIZE) &
					MASK_FIRST_FIELD);
			int nb_stream = ((prmh->stat[i] >> (2*FIELD_SIZE)) &
					 MASK_FIRST_FIELD);
			int pipe = prmh->stat[i] & MASK_FIRST_FIELD;
			int is_capture = prmh->stat[i] & 0x400000;
			u32 err2;

			if (prmh->stat[i] & 0x800000) {	/* if BIT_END */
				dev_dbg(&mgr->pci->dev,
					"TASKLET : End%sPipe %d\n",
					    is_capture ? "Record" : "Play",
					    pipe);
			}
			i++;
			err2 = prmh->stat[i] ? prmh->stat[i] : prmh->stat[i+1];
			if (err2)
				pcxhr_handle_async_err(mgr, err2,
						       PCXHR_ERR_PIPE,
						       pipe, is_capture);
			i += 2;
			for (j = 0; j < nb_stream; j++) {
				err2 = prmh->stat[i] ?
					prmh->stat[i] : prmh->stat[i+1];
				if (err2)
					pcxhr_handle_async_err(mgr, err2,
							       PCXHR_ERR_STREAM,
							       pipe,
							       is_capture);
				i += 2;
			}
			for (j = 0; j < nb_audio; j++) {
				err2 = prmh->stat[i] ?
					prmh->stat[i] : prmh->stat[i+1];
				if (err2)
					pcxhr_handle_async_err(mgr, err2,
							       PCXHR_ERR_AUDIO,
							       pipe,
							       is_capture);
				i += 2;
			}
		}
	}
}