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
typedef  scalar_t__ u64 ;
struct brcmf_pno_info {int n_reqs; int /*<<< orphan*/  req_lock; TYPE_1__** reqs; } ;
struct TYPE_2__ {scalar_t__ reqid; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SCAN ; 
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_pno_remove_request(struct brcmf_pno_info *pi, u64 reqid)
{
	int i, err = 0;

	mutex_lock(&pi->req_lock);

	/* find request */
	for (i = 0; i < pi->n_reqs; i++) {
		if (pi->reqs[i]->reqid == reqid)
			break;
	}
	/* request not found */
	if (WARN(i == pi->n_reqs, "reqid not found\n")) {
		err = -ENOENT;
		goto done;
	}

	brcmf_dbg(SCAN, "reqid=%llu\n", reqid);
	pi->n_reqs--;

	/* if last we are done */
	if (!pi->n_reqs || i == pi->n_reqs)
		goto done;

	/* fill the gap with remaining requests */
	while (i <= pi->n_reqs - 1) {
		pi->reqs[i] = pi->reqs[i + 1];
		i++;
	}

done:
	mutex_unlock(&pi->req_lock);
	return err;
}