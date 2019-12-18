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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * AnonymousShmem ; 
 int /*<<< orphan*/  AnonymousShmemSize ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AnonymousShmemDetach(int status, Datum arg)
{
	/* Release anonymous shared memory block, if any. */
	if (AnonymousShmem != NULL)
	{
		if (munmap(AnonymousShmem, AnonymousShmemSize) < 0)
			elog(LOG, "munmap(%p, %zu) failed: %m",
				 AnonymousShmem, AnonymousShmemSize);
		AnonymousShmem = NULL;
	}
}