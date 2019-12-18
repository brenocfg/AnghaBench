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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfkey_mutex ; 
 int /*<<< orphan*/  sk_del_node_init_rcu (struct sock*) ; 

__attribute__((used)) static void pfkey_remove(struct sock *sk)
{
	mutex_lock(&pfkey_mutex);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&pfkey_mutex);
}