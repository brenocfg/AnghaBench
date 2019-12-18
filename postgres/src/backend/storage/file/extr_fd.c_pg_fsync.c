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

/* Variables and functions */
 scalar_t__ SYNC_METHOD_FSYNC_WRITETHROUGH ; 
 int pg_fsync_no_writethrough (int) ; 
 int pg_fsync_writethrough (int) ; 
 scalar_t__ sync_method ; 

int
pg_fsync(int fd)
{
	/* #if is to skip the sync_method test if there's no need for it */
#if defined(HAVE_FSYNC_WRITETHROUGH) && !defined(FSYNC_WRITETHROUGH_IS_FSYNC)
	if (sync_method == SYNC_METHOD_FSYNC_WRITETHROUGH)
		return pg_fsync_writethrough(fd);
	else
#endif
		return pg_fsync_no_writethrough(fd);
}