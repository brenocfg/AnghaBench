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
struct proc_dir_entry {scalar_t__ data; scalar_t__ name; scalar_t__ inline_name; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_dir_entry_cache ; 

void pde_free(struct proc_dir_entry *pde)
{
	if (S_ISLNK(pde->mode))
		kfree(pde->data);
	if (pde->name != pde->inline_name)
		kfree(pde->name);
	kmem_cache_free(proc_dir_entry_cache, pde);
}