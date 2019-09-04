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
struct tb {int /*<<< orphan*/  nhi; } ;
struct icm {int /*<<< orphan*/  (* save_devices ) (struct tb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NHI_MAILBOX_DRV_UNLOADS ; 
 int /*<<< orphan*/  nhi_mailbox_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tb*) ; 
 struct icm* tb_priv (struct tb*) ; 

__attribute__((used)) static int icm_suspend(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);

	if (icm->save_devices)
		icm->save_devices(tb);

	nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DRV_UNLOADS, 0);
	return 0;
}