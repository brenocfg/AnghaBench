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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum vmmdev_hgcm_function_parameter_type { ____Placeholder_vmmdev_hgcm_function_parameter_type } vmmdev_hgcm_function_parameter_type ;

/* Variables and functions */
 int /*<<< orphan*/  VMMDEV_HGCM_F_PARM_DIRECTION_BOTH ; 
 int /*<<< orphan*/  VMMDEV_HGCM_F_PARM_DIRECTION_FROM_HOST ; 
 int /*<<< orphan*/  VMMDEV_HGCM_F_PARM_DIRECTION_TO_HOST ; 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR 133 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_IN 132 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL 131 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN 130 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT 129 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u32 hgcm_call_linear_addr_type_to_pagelist_flags(
	enum vmmdev_hgcm_function_parameter_type type)
{
	switch (type) {
	default:
		WARN_ON(1);
		/* Fall through */
	case VMMDEV_HGCM_PARM_TYPE_LINADDR:
	case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		return VMMDEV_HGCM_F_PARM_DIRECTION_BOTH;

	case VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
	case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		return VMMDEV_HGCM_F_PARM_DIRECTION_TO_HOST;

	case VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
	case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
		return VMMDEV_HGCM_F_PARM_DIRECTION_FROM_HOST;
	}
}