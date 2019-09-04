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
struct tc_u_hnode {unsigned int divisor; int /*<<< orphan*/ * ht; } ;

/* Variables and functions */
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ht_empty(struct tc_u_hnode *ht)
{
	unsigned int h;

	for (h = 0; h <= ht->divisor; h++)
		if (rcu_access_pointer(ht->ht[h]))
			return false;

	return true;
}