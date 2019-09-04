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
struct timer_list {int dummy; } ;
struct ncsi_request {int enabled; int /*<<< orphan*/  cmd; scalar_t__ rsp; struct ncsi_dev_priv* ndp; } ;
struct ncsi_dev_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct ncsi_request* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncsi_free_request (struct ncsi_request*) ; 
 struct ncsi_request* nr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ncsi_request_timeout(struct timer_list *t)
{
	struct ncsi_request *nr = from_timer(nr, t, timer);
	struct ncsi_dev_priv *ndp = nr->ndp;
	unsigned long flags;

	/* If the request already had associated response,
	 * let the response handler to release it.
	 */
	spin_lock_irqsave(&ndp->lock, flags);
	nr->enabled = false;
	if (nr->rsp || !nr->cmd) {
		spin_unlock_irqrestore(&ndp->lock, flags);
		return;
	}
	spin_unlock_irqrestore(&ndp->lock, flags);

	/* Release the request */
	ncsi_free_request(nr);
}