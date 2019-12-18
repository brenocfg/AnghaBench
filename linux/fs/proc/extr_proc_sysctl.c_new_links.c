#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ctl_table_root {int dummy; } ;
struct ctl_table_header {int nreg; } ;
struct ctl_table {char* procname; int mode; struct ctl_table_root* data; } ;
struct ctl_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set; int /*<<< orphan*/  root; } ;
struct ctl_dir {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IFLNK ; 
 int S_IRWXUGO ; 
 int /*<<< orphan*/  init_header (struct ctl_table_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctl_node*,struct ctl_table*) ; 
 struct ctl_table_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static struct ctl_table_header *new_links(struct ctl_dir *dir, struct ctl_table *table,
	struct ctl_table_root *link_root)
{
	struct ctl_table *link_table, *entry, *link;
	struct ctl_table_header *links;
	struct ctl_node *node;
	char *link_name;
	int nr_entries, name_bytes;

	name_bytes = 0;
	nr_entries = 0;
	for (entry = table; entry->procname; entry++) {
		nr_entries++;
		name_bytes += strlen(entry->procname) + 1;
	}

	links = kzalloc(sizeof(struct ctl_table_header) +
			sizeof(struct ctl_node)*nr_entries +
			sizeof(struct ctl_table)*(nr_entries + 1) +
			name_bytes,
			GFP_KERNEL);

	if (!links)
		return NULL;

	node = (struct ctl_node *)(links + 1);
	link_table = (struct ctl_table *)(node + nr_entries);
	link_name = (char *)&link_table[nr_entries + 1];

	for (link = link_table, entry = table; entry->procname; link++, entry++) {
		int len = strlen(entry->procname) + 1;
		memcpy(link_name, entry->procname, len);
		link->procname = link_name;
		link->mode = S_IFLNK|S_IRWXUGO;
		link->data = link_root;
		link_name += len;
	}
	init_header(links, dir->header.root, dir->header.set, node, link_table);
	links->nreg = nr_entries;

	return links;
}