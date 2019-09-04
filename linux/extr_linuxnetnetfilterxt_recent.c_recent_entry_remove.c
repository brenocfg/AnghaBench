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
struct recent_table {int /*<<< orphan*/  entries; } ;
struct recent_entry {int /*<<< orphan*/  lru_list; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct recent_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recent_entry_remove(struct recent_table *t, struct recent_entry *e)
{
	list_del(&e->list);
	list_del(&e->lru_list);
	kfree(e);
	t->entries--;
}