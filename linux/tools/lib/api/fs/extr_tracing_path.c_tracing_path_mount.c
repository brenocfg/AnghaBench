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
 char* tracing_path_debugfs_mount () ; 
 char* tracing_path_tracefs_mount () ; 

const char *tracing_path_mount(void)
{
	const char *mnt;

	mnt = tracing_path_tracefs_mount();
	if (mnt)
		return mnt;

	mnt = tracing_path_debugfs_mount();

	return mnt;
}