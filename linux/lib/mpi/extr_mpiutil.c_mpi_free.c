#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_free_limb_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void mpi_free(MPI a)
{
	if (!a)
		return;

	if (a->flags & 4)
		kzfree(a->d);
	else
		mpi_free_limb_space(a->d);

	if (a->flags & ~7)
		pr_info("invalid flag value in mpi\n");
	kfree(a);
}