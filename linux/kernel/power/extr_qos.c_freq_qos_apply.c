#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct freq_qos_request {int type; int /*<<< orphan*/  pnode; TYPE_1__* qos; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum pm_qos_req_action { ____Placeholder_pm_qos_req_action } pm_qos_req_action ;
struct TYPE_2__ {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  min_freq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FREQ_QOS_MAX 129 
#define  FREQ_QOS_MIN 128 
 int pm_qos_update_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int freq_qos_apply(struct freq_qos_request *req,
			  enum pm_qos_req_action action, s32 value)
{
	int ret;

	switch(req->type) {
	case FREQ_QOS_MIN:
		ret = pm_qos_update_target(&req->qos->min_freq, &req->pnode,
					   action, value);
		break;
	case FREQ_QOS_MAX:
		ret = pm_qos_update_target(&req->qos->max_freq, &req->pnode,
					   action, value);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}