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
struct rsc_mgr {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct srcimp_mgr {struct rsc_mgr mgr; } ;
struct imapper {int /*<<< orphan*/  addr; int /*<<< orphan*/  next; int /*<<< orphan*/  user; int /*<<< orphan*/  slot; } ;
struct hw {int /*<<< orphan*/  (* srcimp_mgr_commit_write ) (struct hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* srcimp_mgr_set_imapaddr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* srcimp_mgr_set_imapnxt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* srcimp_mgr_set_imapuser ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* srcimp_mgr_set_imaparc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srcimp_map_op(void *data, struct imapper *entry)
{
	struct rsc_mgr *mgr = &((struct srcimp_mgr *)data)->mgr;
	struct hw *hw = mgr->hw;

	hw->srcimp_mgr_set_imaparc(mgr->ctrl_blk, entry->slot);
	hw->srcimp_mgr_set_imapuser(mgr->ctrl_blk, entry->user);
	hw->srcimp_mgr_set_imapnxt(mgr->ctrl_blk, entry->next);
	hw->srcimp_mgr_set_imapaddr(mgr->ctrl_blk, entry->addr);
	hw->srcimp_mgr_commit_write(mgr->hw, mgr->ctrl_blk);

	return 0;
}