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
struct request_sock {int /*<<< orphan*/  rsk_refcnt; int /*<<< orphan*/  rsk_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_PINNED ; 
 int /*<<< orphan*/  inet_ehash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  req_to_sk (struct request_sock*) ; 
 int /*<<< orphan*/  reqsk_timer_handler ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reqsk_queue_hash_req(struct request_sock *req,
				 unsigned long timeout)
{
	timer_setup(&req->rsk_timer, reqsk_timer_handler, TIMER_PINNED);
	mod_timer(&req->rsk_timer, jiffies + timeout);

	inet_ehash_insert(req_to_sk(req), NULL);
	/* before letting lookups find us, make sure all req fields
	 * are committed to memory and refcnt initialized.
	 */
	smp_wmb();
	refcount_set(&req->rsk_refcnt, 2 + 1);
}