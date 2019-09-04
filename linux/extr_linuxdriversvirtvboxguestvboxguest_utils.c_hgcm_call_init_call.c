#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ linear_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ pointer; } ;
struct vmmdev_hgcm_function_parameter {int type; TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  result; scalar_t__ flags; } ;
struct vmmdev_hgcm_call {int client_id; int function; int parm_count; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  VINF_SUCCESS ; 
 struct vmmdev_hgcm_function_parameter* VMMDEV_HGCM_CALL_PARMS (struct vmmdev_hgcm_call*) ; 
#define  VMMDEV_HGCM_PARM_TYPE_32BIT 135 
#define  VMMDEV_HGCM_PARM_TYPE_64BIT 134 
 int VMMDEV_HGCM_PARM_TYPE_INVALID ; 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR 133 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_IN 132 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL 131 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN 130 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT 129 
#define  VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hgcm_call_init_linaddr (struct vmmdev_hgcm_call*,struct vmmdev_hgcm_function_parameter*,void*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void hgcm_call_init_call(
	struct vmmdev_hgcm_call *call, u32 client_id, u32 function,
	const struct vmmdev_hgcm_function_parameter *src_parm,
	u32 parm_count, void **bounce_bufs)
{
	struct vmmdev_hgcm_function_parameter *dst_parm =
		VMMDEV_HGCM_CALL_PARMS(call);
	u32 i, off_extra = (uintptr_t)(dst_parm + parm_count) - (uintptr_t)call;
	void *buf;

	call->header.flags = 0;
	call->header.result = VINF_SUCCESS;
	call->client_id = client_id;
	call->function = function;
	call->parm_count = parm_count;

	for (i = 0; i < parm_count; i++, src_parm++, dst_parm++) {
		switch (src_parm->type) {
		case VMMDEV_HGCM_PARM_TYPE_32BIT:
		case VMMDEV_HGCM_PARM_TYPE_64BIT:
			*dst_parm = *src_parm;
			break;

		case VMMDEV_HGCM_PARM_TYPE_LINADDR:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_IN:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_OUT:
			hgcm_call_init_linaddr(call, dst_parm, bounce_bufs[i],
					       src_parm->u.pointer.size,
					       src_parm->type, &off_extra);
			break;

		case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_IN:
		case VMMDEV_HGCM_PARM_TYPE_LINADDR_KERNEL_OUT:
			buf = (void *)src_parm->u.pointer.u.linear_addr;
			hgcm_call_init_linaddr(call, dst_parm, buf,
					       src_parm->u.pointer.size,
					       src_parm->type, &off_extra);
			break;

		default:
			WARN_ON(1);
			dst_parm->type = VMMDEV_HGCM_PARM_TYPE_INVALID;
		}
	}
}