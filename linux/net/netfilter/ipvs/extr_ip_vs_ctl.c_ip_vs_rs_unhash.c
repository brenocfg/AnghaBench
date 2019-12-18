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
struct ip_vs_dest {scalar_t__ in_rs_table; int /*<<< orphan*/  d_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip_vs_rs_unhash(struct ip_vs_dest *dest)
{
	/*
	 * Remove it from the rs_table table.
	 */
	if (dest->in_rs_table) {
		hlist_del_rcu(&dest->d_list);
		dest->in_rs_table = 0;
	}
}