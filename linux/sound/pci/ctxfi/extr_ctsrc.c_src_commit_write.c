#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int msr; TYPE_1__* ops; int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct src {scalar_t__ mode; TYPE_2__ rsc; } ;
struct hw {unsigned int (* src_get_dirty ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_commit_write ) (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* src_set_dirty ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* master ) (TYPE_2__*) ;int /*<<< orphan*/  (* index ) (TYPE_2__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ MEMWR ; 
 unsigned int conj_mask ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 unsigned int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub7 (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub9 (TYPE_2__*) ; 

__attribute__((used)) static int src_commit_write(struct src *src)
{
	struct hw *hw;
	int i;
	unsigned int dirty = 0;

	hw = src->rsc.hw;
	src->rsc.ops->master(&src->rsc);
	if (src->rsc.msr > 1) {
		/* Save dirty flags for conjugate resource programming */
		dirty = hw->src_get_dirty(src->rsc.ctrl_blk) & conj_mask;
	}
	hw->src_commit_write(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);

	/* Program conjugate parameter mixer resources */
	if (MEMWR == src->mode)
		return 0;

	for (i = 1; i < src->rsc.msr; i++) {
		src->rsc.ops->next_conj(&src->rsc);
		hw->src_set_dirty(src->rsc.ctrl_blk, dirty);
		hw->src_commit_write(hw, src->rsc.ops->index(&src->rsc),
							src->rsc.ctrl_blk);
	}
	src->rsc.ops->master(&src->rsc);

	return 0;
}