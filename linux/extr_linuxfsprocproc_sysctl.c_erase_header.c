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
struct ctl_table_header {struct ctl_table* ctl_table; } ;
struct ctl_table {scalar_t__ procname; } ;

/* Variables and functions */
 int /*<<< orphan*/  erase_entry (struct ctl_table_header*,struct ctl_table*) ; 

__attribute__((used)) static void erase_header(struct ctl_table_header *head)
{
	struct ctl_table *entry;
	for (entry = head->ctl_table; entry->procname; entry++)
		erase_entry(head, entry);
}