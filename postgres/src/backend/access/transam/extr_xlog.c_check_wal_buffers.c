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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int XLOGChooseNumBuffers () ; 
 int XLOGbuffers ; 

bool
check_wal_buffers(int *newval, void **extra, GucSource source)
{
	/*
	 * -1 indicates a request for auto-tune.
	 */
	if (*newval == -1)
	{
		/*
		 * If we haven't yet changed the boot_val default of -1, just let it
		 * be.  We'll fix it when XLOGShmemSize is called.
		 */
		if (XLOGbuffers == -1)
			return true;

		/* Otherwise, substitute the auto-tune value */
		*newval = XLOGChooseNumBuffers();
	}

	/*
	 * We clamp manually-set values to at least 4 blocks.  Prior to PostgreSQL
	 * 9.1, a minimum of 4 was enforced by guc.c, but since that is no longer
	 * the case, we just silently treat such values as a request for the
	 * minimum.  (We could throw an error instead, but that doesn't seem very
	 * helpful.)
	 */
	if (*newval < 4)
		*newval = 4;

	return true;
}