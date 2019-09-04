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
struct ncsi_request {int used; unsigned int flags; } ;
struct ncsi_dev_priv {int request_id; int /*<<< orphan*/  lock; struct ncsi_request* requests; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ncsi_request*) ; 
 int NCSI_REQ_START_IDX ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct ncsi_request *ncsi_alloc_request(struct ncsi_dev_priv *ndp,
					unsigned int req_flags)
{
	struct ncsi_request *nr = NULL;
	int i, limit = ARRAY_SIZE(ndp->requests);
	unsigned long flags;

	/* Check if there is one available request until the ceiling */
	spin_lock_irqsave(&ndp->lock, flags);
	for (i = ndp->request_id; i < limit; i++) {
		if (ndp->requests[i].used)
			continue;

		nr = &ndp->requests[i];
		nr->used = true;
		nr->flags = req_flags;
		ndp->request_id = i + 1;
		goto found;
	}

	/* Fail back to check from the starting cursor */
	for (i = NCSI_REQ_START_IDX; i < ndp->request_id; i++) {
		if (ndp->requests[i].used)
			continue;

		nr = &ndp->requests[i];
		nr->used = true;
		nr->flags = req_flags;
		ndp->request_id = i + 1;
		goto found;
	}

found:
	spin_unlock_irqrestore(&ndp->lock, flags);
	return nr;
}