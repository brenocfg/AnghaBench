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
struct proc_dir_entry {int /*<<< orphan*/  low_ino; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  pde_free (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_free_inum (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void pde_put(struct proc_dir_entry *pde)
{
	if (refcount_dec_and_test(&pde->refcnt)) {
		proc_free_inum(pde->low_ino);
		pde_free(pde);
	}
}