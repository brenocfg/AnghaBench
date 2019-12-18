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
struct hw {int /*<<< orphan*/  (* amixer_set_y ) (int /*<<< orphan*/ ,unsigned int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct amixer {TYPE_1__ rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int amixer_set_y(struct amixer *amixer, unsigned int y)
{
	struct hw *hw;

	hw = amixer->rsc.hw;
	hw->amixer_set_y(amixer->rsc.ctrl_blk, y);

	return 0;
}