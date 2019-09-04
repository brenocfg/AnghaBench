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
struct timer_list {int dummy; } ;
struct AdapterCtlBlk {int /*<<< orphan*/  scsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_1 ; 
 int /*<<< orphan*/  DC395x_LOCK_IO (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  DC395x_UNLOCK_IO (int /*<<< orphan*/ ,unsigned long) ; 
 struct AdapterCtlBlk* acb ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,struct AdapterCtlBlk*) ; 
 struct AdapterCtlBlk* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waiting_process_next (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  waiting_timer ; 

__attribute__((used)) static void waiting_timeout(struct timer_list *t)
{
	unsigned long flags;
	struct AdapterCtlBlk *acb = from_timer(acb, t, waiting_timer);
	dprintkdbg(DBG_1,
		"waiting_timeout: Queue woken up by timer. acb=%p\n", acb);
	DC395x_LOCK_IO(acb->scsi_host, flags);
	waiting_process_next(acb);
	DC395x_UNLOCK_IO(acb->scsi_host, flags);
}