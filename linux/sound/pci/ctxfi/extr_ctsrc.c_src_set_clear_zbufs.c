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
struct TYPE_2__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct src {TYPE_1__ rsc; } ;
struct hw {int /*<<< orphan*/  (* src_set_clear_zbufs ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int src_set_clear_zbufs(struct src *src)
{
	struct hw *hw;

	hw = src->rsc.hw;
	hw->src_set_clear_zbufs(src->rsc.ctrl_blk, 1);

	return 0;
}