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
struct hw {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_card_shutdown (struct hw*) ; 
 int /*<<< orphan*/  kfree (struct hw*) ; 

int destroy_20k2_hw_obj(struct hw *hw)
{
	if (hw->io_base)
		hw_card_shutdown(hw);

	kfree(hw);
	return 0;
}