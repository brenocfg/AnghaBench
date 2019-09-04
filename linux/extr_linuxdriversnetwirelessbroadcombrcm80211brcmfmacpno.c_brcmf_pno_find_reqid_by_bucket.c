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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct brcmf_pno_info {size_t n_reqs; int /*<<< orphan*/  req_lock; TYPE_1__** reqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  reqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u64 brcmf_pno_find_reqid_by_bucket(struct brcmf_pno_info *pi, u32 bucket)
{
	u64 reqid = 0;

	mutex_lock(&pi->req_lock);

	if (bucket < pi->n_reqs)
		reqid = pi->reqs[bucket]->reqid;

	mutex_unlock(&pi->req_lock);
	return reqid;
}