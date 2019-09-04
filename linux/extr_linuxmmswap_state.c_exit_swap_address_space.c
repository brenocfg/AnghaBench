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
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct address_space*) ; 
 scalar_t__* nr_swapper_spaces ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct address_space*,int /*<<< orphan*/ *) ; 
 struct address_space** swapper_spaces ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void exit_swap_address_space(unsigned int type)
{
	struct address_space *spaces;

	spaces = swapper_spaces[type];
	nr_swapper_spaces[type] = 0;
	rcu_assign_pointer(swapper_spaces[type], NULL);
	synchronize_rcu();
	kvfree(spaces);
}