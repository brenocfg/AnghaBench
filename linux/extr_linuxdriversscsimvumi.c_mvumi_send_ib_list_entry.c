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
struct mvumi_hba {int ib_cur_slot; TYPE_1__* regs; int /*<<< orphan*/  ib_shadow; } ;
struct TYPE_2__ {int /*<<< orphan*/  inb_write_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvumi_send_ib_list_entry(struct mvumi_hba *mhba)
{
	iowrite32(0xffff, mhba->ib_shadow);
	iowrite32(mhba->ib_cur_slot, mhba->regs->inb_write_pointer);
}