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
typedef  int /*<<< orphan*/  uint ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct tipc_sock {int published; scalar_t__ pub_count; int /*<<< orphan*/  publications; scalar_t__ portid; struct sock sk; } ;
struct tipc_name_seq {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; } ;
struct publication {int /*<<< orphan*/  binding_sock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EINVAL ; 
 int /*<<< orphan*/  TIPC_CLUSTER_SCOPE ; 
 int /*<<< orphan*/  TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct net* sock_net (struct sock*) ; 
 struct publication* tipc_nametbl_publish (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ tipc_sk_connected (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tipc_sk_publish(struct tipc_sock *tsk, uint scope,
			   struct tipc_name_seq const *seq)
{
	struct sock *sk = &tsk->sk;
	struct net *net = sock_net(sk);
	struct publication *publ;
	u32 key;

	if (scope != TIPC_NODE_SCOPE)
		scope = TIPC_CLUSTER_SCOPE;

	if (tipc_sk_connected(sk))
		return -EINVAL;
	key = tsk->portid + tsk->pub_count + 1;
	if (key == tsk->portid)
		return -EADDRINUSE;

	publ = tipc_nametbl_publish(net, seq->type, seq->lower, seq->upper,
				    scope, tsk->portid, key);
	if (unlikely(!publ))
		return -EINVAL;

	list_add(&publ->binding_sock, &tsk->publications);
	tsk->pub_count++;
	tsk->published = 1;
	return 0;
}