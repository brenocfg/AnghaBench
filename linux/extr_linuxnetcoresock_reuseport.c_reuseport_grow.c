#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sock_reuseport {unsigned int max_socks; int num_socks; TYPE_1__** socks; int /*<<< orphan*/  synq_overflow_ts; int /*<<< orphan*/  bind_inany; int /*<<< orphan*/  reuseport_id; int /*<<< orphan*/  prog; } ;
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_reuseport_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t U16_MAX ; 
 struct sock_reuseport* __reuseport_alloc (size_t) ; 
 int /*<<< orphan*/  kfree_rcu (struct sock_reuseport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sock_reuseport*) ; 

__attribute__((used)) static struct sock_reuseport *reuseport_grow(struct sock_reuseport *reuse)
{
	struct sock_reuseport *more_reuse;
	u32 more_socks_size, i;

	more_socks_size = reuse->max_socks * 2U;
	if (more_socks_size > U16_MAX)
		return NULL;

	more_reuse = __reuseport_alloc(more_socks_size);
	if (!more_reuse)
		return NULL;

	more_reuse->max_socks = more_socks_size;
	more_reuse->num_socks = reuse->num_socks;
	more_reuse->prog = reuse->prog;
	more_reuse->reuseport_id = reuse->reuseport_id;
	more_reuse->bind_inany = reuse->bind_inany;

	memcpy(more_reuse->socks, reuse->socks,
	       reuse->num_socks * sizeof(struct sock *));
	more_reuse->synq_overflow_ts = READ_ONCE(reuse->synq_overflow_ts);

	for (i = 0; i < reuse->num_socks; ++i)
		rcu_assign_pointer(reuse->socks[i]->sk_reuseport_cb,
				   more_reuse);

	/* Note: we use kfree_rcu here instead of reuseport_free_rcu so
	 * that reuse and more_reuse can temporarily share a reference
	 * to prog.
	 */
	kfree_rcu(reuse, rcu);
	return more_reuse;
}