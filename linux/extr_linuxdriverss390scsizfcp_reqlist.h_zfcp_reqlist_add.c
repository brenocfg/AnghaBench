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
struct zfcp_reqlist {int /*<<< orphan*/  lock; int /*<<< orphan*/ * buckets; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  list; int /*<<< orphan*/  req_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int zfcp_reqlist_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void zfcp_reqlist_add(struct zfcp_reqlist *rl,
				    struct zfcp_fsf_req *req)
{
	unsigned int i;
	unsigned long flags;

	i = zfcp_reqlist_hash(req->req_id);

	spin_lock_irqsave(&rl->lock, flags);
	list_add_tail(&req->list, &rl->buckets[i]);
	spin_unlock_irqrestore(&rl->lock, flags);
}