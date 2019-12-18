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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,struct hlist_head*) ; 
 int /*<<< orphan*/  sk_unhashed (struct sock*) ; 

__attribute__((used)) static void __unix_insert_socket(struct hlist_head *list, struct sock *sk)
{
	WARN_ON(!sk_unhashed(sk));
	sk_add_node(sk, list);
}