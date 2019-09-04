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
struct proc_dir_entry {int dummy; } ;
struct nubus_proc_pde_data {int dummy; } ;
struct nubus_dirent {int type; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  nubus_dirptr (struct nubus_dirent const*) ; 
 struct nubus_proc_pde_data* nubus_proc_alloc_pde_data (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nubus_proc_rsrc_show ; 
 int /*<<< orphan*/  proc_create_single_data (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ ,struct nubus_proc_pde_data*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void nubus_proc_add_rsrc_mem(struct proc_dir_entry *procdir,
			     const struct nubus_dirent *ent,
			     unsigned int size)
{
	char name[9];
	struct nubus_proc_pde_data *pde_data;

	if (!procdir)
		return;

	snprintf(name, sizeof(name), "%x", ent->type);
	if (size)
		pde_data = nubus_proc_alloc_pde_data(nubus_dirptr(ent), size);
	else
		pde_data = NULL;
	proc_create_single_data(name, S_IFREG | 0444, procdir,
			nubus_proc_rsrc_show, pde_data);
}