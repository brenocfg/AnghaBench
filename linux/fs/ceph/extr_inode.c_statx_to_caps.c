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
typedef  int u32 ;

/* Variables and functions */
 int CEPH_CAP_AUTH_SHARED ; 
 int CEPH_CAP_FILE_SHARED ; 
 int CEPH_CAP_LINK_SHARED ; 
 int CEPH_CAP_XATTR_SHARED ; 
 int STATX_ATIME ; 
 int STATX_BLOCKS ; 
 int STATX_BTIME ; 
 int STATX_CTIME ; 
 int STATX_GID ; 
 int STATX_MODE ; 
 int STATX_MTIME ; 
 int STATX_NLINK ; 
 int STATX_SIZE ; 
 int STATX_UID ; 

__attribute__((used)) static int statx_to_caps(u32 want)
{
	int mask = 0;

	if (want & (STATX_MODE|STATX_UID|STATX_GID|STATX_CTIME|STATX_BTIME))
		mask |= CEPH_CAP_AUTH_SHARED;

	if (want & (STATX_NLINK|STATX_CTIME))
		mask |= CEPH_CAP_LINK_SHARED;

	if (want & (STATX_ATIME|STATX_MTIME|STATX_CTIME|STATX_SIZE|
		    STATX_BLOCKS))
		mask |= CEPH_CAP_FILE_SHARED;

	if (want & (STATX_CTIME))
		mask |= CEPH_CAP_XATTR_SHARED;

	return mask;
}