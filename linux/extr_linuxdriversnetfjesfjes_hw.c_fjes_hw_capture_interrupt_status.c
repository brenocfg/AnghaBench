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
typedef  int /*<<< orphan*/  u32 ;
struct fjes_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSCT_IS ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 

u32 fjes_hw_capture_interrupt_status(struct fjes_hw *hw)
{
	u32 cur_is;

	cur_is = rd32(XSCT_IS);

	return cur_is;
}