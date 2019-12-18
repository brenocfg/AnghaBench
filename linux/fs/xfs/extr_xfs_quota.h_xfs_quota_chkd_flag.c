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
typedef  int uint ;

/* Variables and functions */
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 
 int XFS_GQUOTA_CHKD ; 
 int XFS_PQUOTA_CHKD ; 
 int XFS_UQUOTA_CHKD ; 

__attribute__((used)) static inline uint
xfs_quota_chkd_flag(
	uint		dqtype)
{
	switch (dqtype) {
	case XFS_DQ_USER:
		return XFS_UQUOTA_CHKD;
	case XFS_DQ_GROUP:
		return XFS_GQUOTA_CHKD;
	case XFS_DQ_PROJ:
		return XFS_PQUOTA_CHKD;
	default:
		return 0;
	}
}