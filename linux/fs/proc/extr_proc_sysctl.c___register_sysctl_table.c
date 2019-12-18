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
struct TYPE_2__ {int /*<<< orphan*/  nreg; struct ctl_table_root* root; } ;
struct ctl_dir {TYPE_1__ header; } ;
struct ctl_table_set {struct ctl_dir dir; } ;
struct ctl_table_root {int dummy; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {scalar_t__ procname; } ;
struct ctl_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ctl_dir*) ; 
 int /*<<< orphan*/  drop_sysctl_table (TYPE_1__*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 struct ctl_dir* get_subdir (struct ctl_dir*,char const*,int) ; 
 int /*<<< orphan*/  init_header (struct ctl_table_header*,struct ctl_table_root*,struct ctl_table_set*,struct ctl_node*,struct ctl_table*) ; 
 scalar_t__ insert_header (struct ctl_dir*,struct ctl_table_header*) ; 
 int /*<<< orphan*/  kfree (struct ctl_table_header*) ; 
 struct ctl_table_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ sysctl_check_table (char const*,struct ctl_table*) ; 
 int /*<<< orphan*/  sysctl_lock ; 

struct ctl_table_header *__register_sysctl_table(
	struct ctl_table_set *set,
	const char *path, struct ctl_table *table)
{
	struct ctl_table_root *root = set->dir.header.root;
	struct ctl_table_header *header;
	const char *name, *nextname;
	struct ctl_dir *dir;
	struct ctl_table *entry;
	struct ctl_node *node;
	int nr_entries = 0;

	for (entry = table; entry->procname; entry++)
		nr_entries++;

	header = kzalloc(sizeof(struct ctl_table_header) +
			 sizeof(struct ctl_node)*nr_entries, GFP_KERNEL);
	if (!header)
		return NULL;

	node = (struct ctl_node *)(header + 1);
	init_header(header, root, set, node, table);
	if (sysctl_check_table(path, table))
		goto fail;

	spin_lock(&sysctl_lock);
	dir = &set->dir;
	/* Reference moved down the diretory tree get_subdir */
	dir->header.nreg++;
	spin_unlock(&sysctl_lock);

	/* Find the directory for the ctl_table */
	for (name = path; name; name = nextname) {
		int namelen;
		nextname = strchr(name, '/');
		if (nextname) {
			namelen = nextname - name;
			nextname++;
		} else {
			namelen = strlen(name);
		}
		if (namelen == 0)
			continue;

		dir = get_subdir(dir, name, namelen);
		if (IS_ERR(dir))
			goto fail;
	}

	spin_lock(&sysctl_lock);
	if (insert_header(dir, header))
		goto fail_put_dir_locked;

	drop_sysctl_table(&dir->header);
	spin_unlock(&sysctl_lock);

	return header;

fail_put_dir_locked:
	drop_sysctl_table(&dir->header);
	spin_unlock(&sysctl_lock);
fail:
	kfree(header);
	dump_stack();
	return NULL;
}