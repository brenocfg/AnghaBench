#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int a; scalar_t__ c; scalar_t__ b; } ;
struct TYPE_4__ {TYPE_1__ value; } ;
struct tee_param {int attr; TYPE_2__ u; } ;
struct tee_device {int dummy; } ;
struct tee_context {struct tee_device* teedev; } ;
struct optee_supp_req {size_t func; size_t num_params; int /*<<< orphan*/  param; } ;
struct optee_supp {int req_id; int /*<<< orphan*/  mutex; int /*<<< orphan*/  reqs_c; } ;
struct optee {struct optee_supp supp; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ IS_ERR (struct optee_supp_req*) ; 
 int PTR_ERR (struct optee_supp_req*) ; 
 int TEE_IOCTL_PARAM_ATTR_META ; 
 int TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT ; 
 int /*<<< orphan*/  memcpy (struct tee_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int supp_check_recv_params (size_t,struct tee_param*,size_t*) ; 
 struct optee_supp_req* supp_pop_entry (struct optee_supp*,size_t,int*) ; 
 struct optee* tee_get_drvdata (struct tee_device*) ; 
 scalar_t__ wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int optee_supp_recv(struct tee_context *ctx, u32 *func, u32 *num_params,
		    struct tee_param *param)
{
	struct tee_device *teedev = ctx->teedev;
	struct optee *optee = tee_get_drvdata(teedev);
	struct optee_supp *supp = &optee->supp;
	struct optee_supp_req *req = NULL;
	int id;
	size_t num_meta;
	int rc;

	rc = supp_check_recv_params(*num_params, param, &num_meta);
	if (rc)
		return rc;

	while (true) {
		mutex_lock(&supp->mutex);
		req = supp_pop_entry(supp, *num_params - num_meta, &id);
		mutex_unlock(&supp->mutex);

		if (req) {
			if (IS_ERR(req))
				return PTR_ERR(req);
			break;
		}

		/*
		 * If we didn't get a request we'll block in
		 * wait_for_completion() to avoid needless spinning.
		 *
		 * This is where supplicant will be hanging most of
		 * the time, let's make this interruptable so we
		 * can easily restart supplicant if needed.
		 */
		if (wait_for_completion_interruptible(&supp->reqs_c))
			return -ERESTARTSYS;
	}

	if (num_meta) {
		/*
		 * tee-supplicant support meta parameters -> requsts can be
		 * processed asynchronously.
		 */
		param->attr = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT |
			      TEE_IOCTL_PARAM_ATTR_META;
		param->u.value.a = id;
		param->u.value.b = 0;
		param->u.value.c = 0;
	} else {
		mutex_lock(&supp->mutex);
		supp->req_id = id;
		mutex_unlock(&supp->mutex);
	}

	*func = req->func;
	*num_params = req->num_params + num_meta;
	memcpy(param + num_meta, req->param,
	       sizeof(struct tee_param) * req->num_params);

	return 0;
}