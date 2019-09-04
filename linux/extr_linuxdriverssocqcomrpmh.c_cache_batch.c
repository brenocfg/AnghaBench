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
struct rpmh_ctrlr {int /*<<< orphan*/  cache_lock; int /*<<< orphan*/  batch_cache; } ;
struct batch_cache_req {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cache_batch(struct rpmh_ctrlr *ctrlr, struct batch_cache_req *req)
{
	unsigned long flags;

	spin_lock_irqsave(&ctrlr->cache_lock, flags);
	list_add_tail(&req->list, &ctrlr->batch_cache);
	spin_unlock_irqrestore(&ctrlr->cache_lock, flags);
}