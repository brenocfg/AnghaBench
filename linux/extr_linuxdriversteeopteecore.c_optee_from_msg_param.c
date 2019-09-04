#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tee_shm {int dummy; } ;
struct TYPE_13__ {struct tee_shm* shm; scalar_t__ shm_offs; scalar_t__ size; } ;
struct TYPE_8__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_14__ {TYPE_6__ memref; TYPE_1__ value; } ;
struct tee_param {int attr; TYPE_7__ u; } ;
struct TYPE_11__ {scalar_t__ offs; scalar_t__ shm_ref; scalar_t__ size; } ;
struct TYPE_10__ {scalar_t__ buf_ptr; scalar_t__ shm_ref; scalar_t__ size; } ;
struct TYPE_9__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_12__ {TYPE_4__ rmem; TYPE_3__ tmem; TYPE_2__ value; } ;
struct optee_msg_param {int attr; TYPE_5__ u; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int OPTEE_MSG_ATTR_TYPE_MASK ; 
#define  OPTEE_MSG_ATTR_TYPE_NONE 137 
#define  OPTEE_MSG_ATTR_TYPE_RMEM_INOUT 136 
#define  OPTEE_MSG_ATTR_TYPE_RMEM_INPUT 135 
#define  OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT 134 
#define  OPTEE_MSG_ATTR_TYPE_TMEM_INOUT 133 
#define  OPTEE_MSG_ATTR_TYPE_TMEM_INPUT 132 
#define  OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT 131 
#define  OPTEE_MSG_ATTR_TYPE_VALUE_INOUT 130 
#define  OPTEE_MSG_ATTR_TYPE_VALUE_INPUT 129 
#define  OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT 128 
 int /*<<< orphan*/  TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT ; 
 int TEE_IOCTL_PARAM_ATTR_TYPE_NONE ; 
 int /*<<< orphan*/  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int tee_shm_get_pa (struct tee_shm*,size_t,scalar_t__*) ; 

int optee_from_msg_param(struct tee_param *params, size_t num_params,
			 const struct optee_msg_param *msg_params)
{
	int rc;
	size_t n;
	struct tee_shm *shm;
	phys_addr_t pa;

	for (n = 0; n < num_params; n++) {
		struct tee_param *p = params + n;
		const struct optee_msg_param *mp = msg_params + n;
		u32 attr = mp->attr & OPTEE_MSG_ATTR_TYPE_MASK;

		switch (attr) {
		case OPTEE_MSG_ATTR_TYPE_NONE:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_NONE;
			memset(&p->u, 0, sizeof(p->u));
			break;
		case OPTEE_MSG_ATTR_TYPE_VALUE_INPUT:
		case OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT:
		case OPTEE_MSG_ATTR_TYPE_VALUE_INOUT:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT +
				  attr - OPTEE_MSG_ATTR_TYPE_VALUE_INPUT;
			p->u.value.a = mp->u.value.a;
			p->u.value.b = mp->u.value.b;
			p->u.value.c = mp->u.value.c;
			break;
		case OPTEE_MSG_ATTR_TYPE_TMEM_INPUT:
		case OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT:
		case OPTEE_MSG_ATTR_TYPE_TMEM_INOUT:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT +
				  attr - OPTEE_MSG_ATTR_TYPE_TMEM_INPUT;
			p->u.memref.size = mp->u.tmem.size;
			shm = (struct tee_shm *)(unsigned long)
				mp->u.tmem.shm_ref;
			if (!shm) {
				p->u.memref.shm_offs = 0;
				p->u.memref.shm = NULL;
				break;
			}
			rc = tee_shm_get_pa(shm, 0, &pa);
			if (rc)
				return rc;
			p->u.memref.shm_offs = mp->u.tmem.buf_ptr - pa;
			p->u.memref.shm = shm;

			/* Check that the memref is covered by the shm object */
			if (p->u.memref.size) {
				size_t o = p->u.memref.shm_offs +
					   p->u.memref.size - 1;

				rc = tee_shm_get_pa(shm, o, NULL);
				if (rc)
					return rc;
			}
			break;
		case OPTEE_MSG_ATTR_TYPE_RMEM_INPUT:
		case OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT:
		case OPTEE_MSG_ATTR_TYPE_RMEM_INOUT:
			p->attr = TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT +
				  attr - OPTEE_MSG_ATTR_TYPE_RMEM_INPUT;
			p->u.memref.size = mp->u.rmem.size;
			shm = (struct tee_shm *)(unsigned long)
				mp->u.rmem.shm_ref;

			if (!shm) {
				p->u.memref.shm_offs = 0;
				p->u.memref.shm = NULL;
				break;
			}
			p->u.memref.shm_offs = mp->u.rmem.offs;
			p->u.memref.shm = shm;

			break;

		default:
			return -EINVAL;
		}
	}
	return 0;
}