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
struct TYPE_2__ {int data; } ;
struct amixer_rsc_ctrl_blk {TYPE_1__ dirty; } ;

/* Variables and functions */

__attribute__((used)) static int amixer_set_dirty_all(void *blk)
{
	((struct amixer_rsc_ctrl_blk *)blk)->dirty.data = ~(0x0);
	return 0;
}