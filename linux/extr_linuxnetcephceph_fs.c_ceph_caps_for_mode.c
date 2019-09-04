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
 int CEPH_CAP_AUTH_EXCL ; 
 int CEPH_CAP_AUTH_SHARED ; 
 int CEPH_CAP_FILE_BUFFER ; 
 int CEPH_CAP_FILE_CACHE ; 
 int CEPH_CAP_FILE_EXCL ; 
 int CEPH_CAP_FILE_LAZYIO ; 
 int CEPH_CAP_FILE_RD ; 
 int CEPH_CAP_FILE_SHARED ; 
 int CEPH_CAP_FILE_WR ; 
 int CEPH_CAP_PIN ; 
 int CEPH_CAP_XATTR_EXCL ; 
 int CEPH_CAP_XATTR_SHARED ; 
 int CEPH_FILE_MODE_LAZY ; 
 int CEPH_FILE_MODE_RD ; 
 int CEPH_FILE_MODE_WR ; 

int ceph_caps_for_mode(int mode)
{
	int caps = CEPH_CAP_PIN;

	if (mode & CEPH_FILE_MODE_RD)
		caps |= CEPH_CAP_FILE_SHARED |
			CEPH_CAP_FILE_RD | CEPH_CAP_FILE_CACHE;
	if (mode & CEPH_FILE_MODE_WR)
		caps |= CEPH_CAP_FILE_EXCL |
			CEPH_CAP_FILE_WR | CEPH_CAP_FILE_BUFFER |
			CEPH_CAP_AUTH_SHARED | CEPH_CAP_AUTH_EXCL |
			CEPH_CAP_XATTR_SHARED | CEPH_CAP_XATTR_EXCL;
	if (mode & CEPH_FILE_MODE_LAZY)
		caps |= CEPH_CAP_FILE_LAZYIO;

	return caps;
}