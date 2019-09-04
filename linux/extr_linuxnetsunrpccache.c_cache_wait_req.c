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
struct cache_deferred_req {int /*<<< orphan*/  hash; int /*<<< orphan*/  revisit; } ;
struct thread_deferred_req {int /*<<< orphan*/  completion; struct cache_deferred_req handle; } ;
struct cache_req {int /*<<< orphan*/  thread_wait; } ;
struct cache_head {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_PENDING ; 
 int /*<<< orphan*/  COMPLETION_INITIALIZER_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unhash_deferred_req (struct cache_deferred_req*) ; 
 int /*<<< orphan*/  cache_defer_lock ; 
 int /*<<< orphan*/  cache_restart_thread ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_deferral (struct cache_deferred_req*,struct cache_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_wait_req(struct cache_req *req, struct cache_head *item)
{
	struct thread_deferred_req sleeper;
	struct cache_deferred_req *dreq = &sleeper.handle;

	sleeper.completion = COMPLETION_INITIALIZER_ONSTACK(sleeper.completion);
	dreq->revisit = cache_restart_thread;

	setup_deferral(dreq, item, 0);

	if (!test_bit(CACHE_PENDING, &item->flags) ||
	    wait_for_completion_interruptible_timeout(
		    &sleeper.completion, req->thread_wait) <= 0) {
		/* The completion wasn't completed, so we need
		 * to clean up
		 */
		spin_lock(&cache_defer_lock);
		if (!hlist_unhashed(&sleeper.handle.hash)) {
			__unhash_deferred_req(&sleeper.handle);
			spin_unlock(&cache_defer_lock);
		} else {
			/* cache_revisit_request already removed
			 * this from the hash table, but hasn't
			 * called ->revisit yet.  It will very soon
			 * and we need to wait for it.
			 */
			spin_unlock(&cache_defer_lock);
			wait_for_completion(&sleeper.completion);
		}
	}
}