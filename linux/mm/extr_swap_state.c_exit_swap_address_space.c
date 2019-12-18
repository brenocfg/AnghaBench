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

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 scalar_t__* nr_swapper_spaces ; 
 int /*<<< orphan*/ ** swapper_spaces ; 

void exit_swap_address_space(unsigned int type)
{
	kvfree(swapper_spaces[type]);
	nr_swapper_spaces[type] = 0;
	swapper_spaces[type] = NULL;
}