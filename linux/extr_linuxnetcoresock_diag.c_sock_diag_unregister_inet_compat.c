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

/* Variables and functions */
 int /*<<< orphan*/ * inet_rcv_compat ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_diag_table_mutex ; 

void sock_diag_unregister_inet_compat(int (*fn)(struct sk_buff *skb, struct nlmsghdr *nlh))
{
	mutex_lock(&sock_diag_table_mutex);
	inet_rcv_compat = NULL;
	mutex_unlock(&sock_diag_table_mutex);
}