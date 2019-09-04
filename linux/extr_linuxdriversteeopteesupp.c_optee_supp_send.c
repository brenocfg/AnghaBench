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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_6__ {TYPE_2__ memref; TYPE_1__ value; } ;
struct tee_param {int attr; TYPE_3__ u; } ;
struct tee_device {int dummy; } ;
struct tee_context {struct tee_device* teedev; } ;
struct optee_supp_req {size_t num_params; int /*<<< orphan*/  c; int /*<<< orphan*/  ret; struct tee_param* param; } ;
struct optee_supp {int /*<<< orphan*/  mutex; } ;
struct optee {struct optee_supp supp; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct optee_supp_req*) ; 
 int PTR_ERR (struct optee_supp_req*) ; 
 int TEE_IOCTL_PARAM_ATTR_TYPE_MASK ; 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT 131 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT 130 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT 129 
#define  TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct optee_supp_req* supp_pop_req (struct optee_supp*,int /*<<< orphan*/ ,struct tee_param*,size_t*) ; 
 struct optee* tee_get_drvdata (struct tee_device*) ; 

int optee_supp_send(struct tee_context *ctx, u32 ret, u32 num_params,
		    struct tee_param *param)
{
	struct tee_device *teedev = ctx->teedev;
	struct optee *optee = tee_get_drvdata(teedev);
	struct optee_supp *supp = &optee->supp;
	struct optee_supp_req *req;
	size_t n;
	size_t num_meta;

	mutex_lock(&supp->mutex);
	req = supp_pop_req(supp, num_params, param, &num_meta);
	mutex_unlock(&supp->mutex);

	if (IS_ERR(req)) {
		/* Something is wrong, let supplicant restart. */
		return PTR_ERR(req);
	}

	/* Update out and in/out parameters */
	for (n = 0; n < req->num_params; n++) {
		struct tee_param *p = req->param + n;

		switch (p->attr & TEE_IOCTL_PARAM_ATTR_TYPE_MASK) {
		case TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT:
		case TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT:
			p->u.value.a = param[n + num_meta].u.value.a;
			p->u.value.b = param[n + num_meta].u.value.b;
			p->u.value.c = param[n + num_meta].u.value.c;
			break;
		case TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT:
		case TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT:
			p->u.memref.size = param[n + num_meta].u.memref.size;
			break;
		default:
			break;
		}
	}
	req->ret = ret;

	/* Let the requesting thread continue */
	complete(&req->c);

	return 0;
}