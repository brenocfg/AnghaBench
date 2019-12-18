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
 int ECRYPTFS_SUPPORTED_FILE_VERSION ; 
 int ECRYPTFS_VERSION_MAJOR ; 
 int ECRYPTFS_VERSION_MINOR ; 

void ecryptfs_get_versions(int *major, int *minor, int *file_version)
{
	*major = ECRYPTFS_VERSION_MAJOR;
	*minor = ECRYPTFS_VERSION_MINOR;
	if (file_version)
		*file_version = ECRYPTFS_SUPPORTED_FILE_VERSION;
}