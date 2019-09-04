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
 int EAGAIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
#define  HV_EBADALIGN 132 
#define  HV_EINVAL 131 
#define  HV_ENOACCESS 130 
#define  HV_ENORADDR 129 
#define  HV_EWOULDBLOCK 128 

__attribute__((used)) static char *dax_hv_errno(unsigned long hv_ret, int *ret)
{
	switch (hv_ret) {
	case HV_EBADALIGN:
		*ret = -EFAULT;
		return "HV_EBADALIGN";
	case HV_ENORADDR:
		*ret = -EFAULT;
		return "HV_ENORADDR";
	case HV_EINVAL:
		*ret = -EINVAL;
		return "HV_EINVAL";
	case HV_EWOULDBLOCK:
		*ret = -EAGAIN;
		return "HV_EWOULDBLOCK";
	case HV_ENOACCESS:
		*ret = -EPERM;
		return "HV_ENOACCESS";
	default:
		break;
	}

	*ret = -EIO;
	return "UNKNOWN";
}