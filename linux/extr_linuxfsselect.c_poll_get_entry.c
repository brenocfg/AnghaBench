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
struct poll_wqueues {scalar_t__ inline_index; struct poll_table_page* table; int /*<<< orphan*/  error; struct poll_table_entry* inline_entries; } ;
struct poll_table_page {int /*<<< orphan*/  entry; struct poll_table_page* next; int /*<<< orphan*/  entries; } ;
struct poll_table_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ N_INLINE_POLL_ENTRIES ; 
 scalar_t__ POLL_TABLE_FULL (struct poll_table_page*) ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct poll_table_entry *poll_get_entry(struct poll_wqueues *p)
{
	struct poll_table_page *table = p->table;

	if (p->inline_index < N_INLINE_POLL_ENTRIES)
		return p->inline_entries + p->inline_index++;

	if (!table || POLL_TABLE_FULL(table)) {
		struct poll_table_page *new_table;

		new_table = (struct poll_table_page *) __get_free_page(GFP_KERNEL);
		if (!new_table) {
			p->error = -ENOMEM;
			return NULL;
		}
		new_table->entry = new_table->entries;
		new_table->next = table;
		p->table = new_table;
		table = new_table;
	}

	return table->entry++;
}