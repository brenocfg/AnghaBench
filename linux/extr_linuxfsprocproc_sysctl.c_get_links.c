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
struct ctl_table_root {int dummy; } ;
struct ctl_table_header {int /*<<< orphan*/  nreg; } ;
struct ctl_table {char* procname; struct ctl_table_root* data; int /*<<< orphan*/  mode; } ;
struct ctl_dir {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct ctl_table* find_entry (struct ctl_table_header**,struct ctl_dir*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool get_links(struct ctl_dir *dir,
	struct ctl_table *table, struct ctl_table_root *link_root)
{
	struct ctl_table_header *head;
	struct ctl_table *entry, *link;

	/* Are there links available for every entry in table? */
	for (entry = table; entry->procname; entry++) {
		const char *procname = entry->procname;
		link = find_entry(&head, dir, procname, strlen(procname));
		if (!link)
			return false;
		if (S_ISDIR(link->mode) && S_ISDIR(entry->mode))
			continue;
		if (S_ISLNK(link->mode) && (link->data == link_root))
			continue;
		return false;
	}

	/* The checks passed.  Increase the registration count on the links */
	for (entry = table; entry->procname; entry++) {
		const char *procname = entry->procname;
		link = find_entry(&head, dir, procname, strlen(procname));
		head->nreg++;
	}
	return true;
}