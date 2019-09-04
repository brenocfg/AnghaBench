#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ linear_addr; } ;
struct TYPE_5__ {scalar_t__ size; TYPE_1__ u; } ;
struct TYPE_6__ {TYPE_2__ pointer; } ;
struct vmmdev_hgcm_function_parameter {int type; TYPE_3__ u; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VBG_MAX_HGCM_KERNEL_PARM ; 
#define  VMMDEV_HGCM_PARM_TYPE_32BIT 135 
#define  VMMDEV_HGCM_PARM_TYPE_64BIT 134 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR 133 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_IN 132 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL 131 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN 130 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT 129 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hgcm_call_add_pagelist_size (void*,scalar_t__,size_t*) ; 
 int hgcm_call_preprocess_linaddr (struct vmmdev_hgcm_function_parameter const*,void**,size_t*) ; 
 void** kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hgcm_call_preprocess(
	const struct vmmdev_hgcm_function_parameter *src_parm,
	u32 parm_count, void ***bounce_bufs_ret, size_t *extra)
{
	void *buf, **bounce_bufs = NULL;
	u32 i, len;
	int ret;

	for (i = 0; i < parm_count; i++, src_parm++) {
		switch (src_parm->type) {
		case VMMDEV_HGCM_PARM_TYPE_32BIT:
		case VMMDEV_HGCM_PARM_TYPE_64BIT:
			break;

		case VMMDEV_HGCM_PARM_TYPE_LINADDR:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
			if (!bounce_bufs) {
				bounce_bufs = kcalloc(parm_count,
						      sizeof(void *),
						      GFP_KERNEL);
				if (!bounce_bufs)
					return -ENOMEM;

				*bounce_bufs_ret = bounce_bufs;
			}

			ret = hgcm_call_preprocess_linaddr(src_parm,
							   &bounce_bufs[i],
							   extra);
			if (ret)
				return ret;

			break;

		case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
			buf = (void *)src_parm->u.pointer.u.linear_addr;
			len = src_parm->u.pointer.size;
			if (WARN_ON(len > VBG_MAX_HGCM_KERNEL_PARM))
				return -E2BIG;

			hgcm_call_add_pagelist_size(buf, len, extra);
			break;

		default:
			return -EINVAL;
		}
	}

	return 0;
}