#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * read_file; } ;
typedef  TYPE_1__ SharedTuplestoreAccessor ;

/* Variables and functions */
 int /*<<< orphan*/  BufFileClose (int /*<<< orphan*/ *) ; 

void
sts_end_parallel_scan(SharedTuplestoreAccessor *accessor)
{
	/*
	 * Here we could delete all files if SHARED_TUPLESTORE_SINGLE_PASS, but
	 * we'd probably need a reference count of current parallel scanners so we
	 * could safely do it only when the reference count reaches zero.
	 */
	if (accessor->read_file != NULL)
	{
		BufFileClose(accessor->read_file);
		accessor->read_file = NULL;
	}
}