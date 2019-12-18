#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_sock {int /*<<< orphan*/  rsk_timer; int /*<<< orphan*/  rsk_hash; } ;
struct inet_hashinfo {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_8__ {TYPE_2__* sk_prot; } ;
struct TYPE_6__ {struct inet_hashinfo* hashinfo; } ;
struct TYPE_7__ {TYPE_1__ h; } ;

/* Variables and functions */
 int __sk_nulls_del_node_init_rcu (TYPE_3__*) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * inet_ehash_lockp (struct inet_hashinfo*,int /*<<< orphan*/ ) ; 
 TYPE_3__* req_to_sk (struct request_sock*) ; 
 int /*<<< orphan*/  reqsk_put (struct request_sock*) ; 
 scalar_t__ sk_hashed (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool reqsk_queue_unlink(struct request_sock *req)
{
	struct inet_hashinfo *hashinfo = req_to_sk(req)->sk_prot->h.hashinfo;
	bool found = false;

	if (sk_hashed(req_to_sk(req))) {
		spinlock_t *lock = inet_ehash_lockp(hashinfo, req->rsk_hash);

		spin_lock(lock);
		found = __sk_nulls_del_node_init_rcu(req_to_sk(req));
		spin_unlock(lock);
	}
	if (timer_pending(&req->rsk_timer) && del_timer_sync(&req->rsk_timer))
		reqsk_put(req);
	return found;
}