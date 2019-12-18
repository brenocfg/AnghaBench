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
struct netlbl_af4list {int /*<<< orphan*/  list; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

void netlbl_af4list_remove_entry(struct netlbl_af4list *entry)
{
	entry->valid = 0;
	list_del_rcu(&entry->list);
}