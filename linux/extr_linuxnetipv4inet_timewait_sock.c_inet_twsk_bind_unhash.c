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
struct sock {int dummy; } ;
struct inet_timewait_sock {struct inet_bind_bucket* tw_tb; int /*<<< orphan*/  tw_bind_node; } ;
struct inet_hashinfo {int /*<<< orphan*/  bind_bucket_cachep; } ;
struct inet_bind_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  inet_bind_bucket_destroy (int /*<<< orphan*/ ,struct inet_bind_bucket*) ; 

void inet_twsk_bind_unhash(struct inet_timewait_sock *tw,
			  struct inet_hashinfo *hashinfo)
{
	struct inet_bind_bucket *tb = tw->tw_tb;

	if (!tb)
		return;

	__hlist_del(&tw->tw_bind_node);
	tw->tw_tb = NULL;
	inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
	__sock_put((struct sock *)tw);
}