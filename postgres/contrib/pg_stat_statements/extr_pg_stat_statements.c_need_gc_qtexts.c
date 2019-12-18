#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int extent; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ pgssSharedState ;
struct TYPE_4__ {int mean_query_len; } ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_2__* pgss ; 
 int pgss_max ; 

__attribute__((used)) static bool
need_gc_qtexts(void)
{
	Size		extent;

	/* Read shared extent pointer */
	{
		volatile pgssSharedState *s = (volatile pgssSharedState *) pgss;

		SpinLockAcquire(&s->mutex);
		extent = s->extent;
		SpinLockRelease(&s->mutex);
	}

	/* Don't proceed if file does not exceed 512 bytes per possible entry */
	if (extent < 512 * pgss_max)
		return false;

	/*
	 * Don't proceed if file is less than about 50% bloat.  Nothing can or
	 * should be done in the event of unusually large query texts accounting
	 * for file's large size.  We go to the trouble of maintaining the mean
	 * query length in order to prevent garbage collection from thrashing
	 * uselessly.
	 */
	if (extent < pgss->mean_query_len * pgss_max * 2)
		return false;

	return true;
}