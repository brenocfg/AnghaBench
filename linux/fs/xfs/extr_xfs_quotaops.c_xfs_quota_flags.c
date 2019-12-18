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
 unsigned int FS_QUOTA_GDQ_ACCT ; 
 unsigned int FS_QUOTA_GDQ_ENFD ; 
 unsigned int FS_QUOTA_PDQ_ACCT ; 
 unsigned int FS_QUOTA_PDQ_ENFD ; 
 unsigned int FS_QUOTA_UDQ_ACCT ; 
 unsigned int FS_QUOTA_UDQ_ENFD ; 
 unsigned int XFS_GQUOTA_ACCT ; 
 unsigned int XFS_GQUOTA_ENFD ; 
 unsigned int XFS_PQUOTA_ACCT ; 
 unsigned int XFS_PQUOTA_ENFD ; 
 unsigned int XFS_UQUOTA_ACCT ; 
 unsigned int XFS_UQUOTA_ENFD ; 

__attribute__((used)) static unsigned int
xfs_quota_flags(unsigned int uflags)
{
	unsigned int flags = 0;

	if (uflags & FS_QUOTA_UDQ_ACCT)
		flags |= XFS_UQUOTA_ACCT;
	if (uflags & FS_QUOTA_PDQ_ACCT)
		flags |= XFS_PQUOTA_ACCT;
	if (uflags & FS_QUOTA_GDQ_ACCT)
		flags |= XFS_GQUOTA_ACCT;
	if (uflags & FS_QUOTA_UDQ_ENFD)
		flags |= XFS_UQUOTA_ENFD;
	if (uflags & FS_QUOTA_GDQ_ENFD)
		flags |= XFS_GQUOTA_ENFD;
	if (uflags & FS_QUOTA_PDQ_ENFD)
		flags |= XFS_PQUOTA_ENFD;

	return flags;
}