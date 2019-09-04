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
struct TYPE_4__ {int /*<<< orphan*/  ctrl_blk; TYPE_1__* ops; struct hw* hw; } ;
struct src {TYPE_2__ rsc; } ;
struct hw {int (* src_get_ca ) (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* index ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int stub1 (struct hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static int src_get_ca(struct src *src)
{
	struct hw *hw;

	hw = src->rsc.hw;
	return hw->src_get_ca(hw, src->rsc.ops->index(&src->rsc),
						src->rsc.ctrl_blk);
}