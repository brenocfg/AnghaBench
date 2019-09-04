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
 unsigned int FS_QUOTA_GDQ_ENFD ; 
 unsigned int FS_QUOTA_PDQ_ENFD ; 
 unsigned int FS_QUOTA_UDQ_ENFD ; 
#define  GRPQUOTA 130 
#define  PRJQUOTA 129 
#define  USRQUOTA 128 

unsigned int qtype_enforce_flag(int type)
{
	switch (type) {
	case USRQUOTA:
		return FS_QUOTA_UDQ_ENFD;
	case GRPQUOTA:
		return FS_QUOTA_GDQ_ENFD;
	case PRJQUOTA:
		return FS_QUOTA_PDQ_ENFD;
	}
	return 0;
}