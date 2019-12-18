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
struct proc_dir_entry {int /*<<< orphan*/  pde_unload_completion; int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 scalar_t__ BIAS ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void unuse_pde(struct proc_dir_entry *pde)
{
	if (unlikely(atomic_dec_return(&pde->in_use) == BIAS))
		complete(pde->pde_unload_completion);
}