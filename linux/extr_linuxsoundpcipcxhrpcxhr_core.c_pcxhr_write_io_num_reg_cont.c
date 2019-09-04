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
struct pcxhr_rmh {unsigned int* cmd; int cmd_len; } ;
struct pcxhr_mgr {unsigned int io_num_reg_cont; int /*<<< orphan*/  msg_lock; TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACCESS_IO_WRITE ; 
 unsigned int IO_NUM_REG_CONT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg_nolock (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 

int pcxhr_write_io_num_reg_cont(struct pcxhr_mgr *mgr, unsigned int mask,
				unsigned int value, int *changed)
{
	struct pcxhr_rmh rmh;
	int err;

	mutex_lock(&mgr->msg_lock);
	if ((mgr->io_num_reg_cont & mask) == value) {
		dev_dbg(&mgr->pci->dev,
			"IO_NUM_REG_CONT mask %x already is set to %x\n",
			    mask, value);
		if (changed)
			*changed = 0;
		mutex_unlock(&mgr->msg_lock);
		return 0;	/* already programmed */
	}
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
	rmh.cmd[0] |= IO_NUM_REG_CONT;
	rmh.cmd[1]  = mask;
	rmh.cmd[2]  = value;
	rmh.cmd_len = 3;
	err = pcxhr_send_msg_nolock(mgr, &rmh);
	if (err == 0) {
		mgr->io_num_reg_cont &= ~mask;
		mgr->io_num_reg_cont |= value;
		if (changed)
			*changed = 1;
	}
	mutex_unlock(&mgr->msg_lock);
	return err;
}