#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct mailbox {int* ccbptr; scalar_t__ status; } ;
struct ccb {int* ccbptr; scalar_t__ status; } ;
struct aha1542_hostdata {struct mailbox* ccb; struct mailbox* mb; } ;
struct Scsi_Host {int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int AHA1542_MAILBOXES ; 
 int CMD_MBINIT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  aha1542_intr_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ aha1542_out (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  any2scsi (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_virt_to_bus (struct mailbox*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 struct aha1542_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void setup_mailboxes(struct Scsi_Host *sh)
{
	struct aha1542_hostdata *aha1542 = shost_priv(sh);
	int i;
	struct mailbox *mb = aha1542->mb;
	struct ccb *ccb = aha1542->ccb;

	u8 mb_cmd[5] = { CMD_MBINIT, AHA1542_MAILBOXES, 0, 0, 0};

	for (i = 0; i < AHA1542_MAILBOXES; i++) {
		mb[i].status = mb[AHA1542_MAILBOXES + i].status = 0;
		any2scsi(mb[i].ccbptr, isa_virt_to_bus(&ccb[i]));
	};
	aha1542_intr_reset(sh->io_port);	/* reset interrupts, so they don't block */
	any2scsi((mb_cmd + 2), isa_virt_to_bus(mb));
	if (aha1542_out(sh->io_port, mb_cmd, 5))
		shost_printk(KERN_ERR, sh, "failed setting up mailboxes\n");
	aha1542_intr_reset(sh->io_port);
}