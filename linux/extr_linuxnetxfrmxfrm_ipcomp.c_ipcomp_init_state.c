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
struct xfrm_state {struct ipcomp_data* data; TYPE_1__* calg; scalar_t__ encap; } ;
struct TYPE_5__ {int /*<<< orphan*/  threshold; } ;
struct TYPE_6__ {TYPE_2__ comp; } ;
struct xfrm_algo_desc {TYPE_3__ uinfo; } ;
struct ipcomp_data {int /*<<< orphan*/  threshold; int /*<<< orphan*/  tfms; } ;
struct TYPE_4__ {int /*<<< orphan*/  alg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ipcomp_alloc_scratches () ; 
 int /*<<< orphan*/  ipcomp_alloc_tfms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcomp_free_data (struct ipcomp_data*) ; 
 int /*<<< orphan*/  ipcomp_resource_mutex ; 
 int /*<<< orphan*/  kfree (struct ipcomp_data*) ; 
 struct ipcomp_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct xfrm_algo_desc* xfrm_calg_get_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipcomp_init_state(struct xfrm_state *x)
{
	int err;
	struct ipcomp_data *ipcd;
	struct xfrm_algo_desc *calg_desc;

	err = -EINVAL;
	if (!x->calg)
		goto out;

	if (x->encap)
		goto out;

	err = -ENOMEM;
	ipcd = kzalloc(sizeof(*ipcd), GFP_KERNEL);
	if (!ipcd)
		goto out;

	mutex_lock(&ipcomp_resource_mutex);
	if (!ipcomp_alloc_scratches())
		goto error;

	ipcd->tfms = ipcomp_alloc_tfms(x->calg->alg_name);
	if (!ipcd->tfms)
		goto error;
	mutex_unlock(&ipcomp_resource_mutex);

	calg_desc = xfrm_calg_get_byname(x->calg->alg_name, 0);
	BUG_ON(!calg_desc);
	ipcd->threshold = calg_desc->uinfo.comp.threshold;
	x->data = ipcd;
	err = 0;
out:
	return err;

error:
	ipcomp_free_data(ipcd);
	mutex_unlock(&ipcomp_resource_mutex);
	kfree(ipcd);
	goto out;
}