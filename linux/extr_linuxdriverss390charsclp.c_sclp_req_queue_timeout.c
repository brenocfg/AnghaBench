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
struct sclp_req {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (struct sclp_req*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned long __sclp_req_queue_find_next_timeout () ; 
 struct sclp_req* __sclp_req_queue_remove_expired_req () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_queue_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sclp_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sclp_req_queue_timeout(struct timer_list *unused)
{
	unsigned long flags, expires_next;
	struct sclp_req *req;

	do {
		req = __sclp_req_queue_remove_expired_req();
		if (req && req->callback)
			req->callback(req, req->callback_data);
	} while (req);

	spin_lock_irqsave(&sclp_lock, flags);
	expires_next = __sclp_req_queue_find_next_timeout();
	if (expires_next)
		mod_timer(&sclp_queue_timer, expires_next);
	spin_unlock_irqrestore(&sclp_lock, flags);
}