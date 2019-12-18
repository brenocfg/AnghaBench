#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct sk_msg {TYPE_1__ sg; } ;

/* Variables and functions */
 int __sk_msg_free (struct sock*,struct sk_msg*,int /*<<< orphan*/ ,int) ; 

int sk_msg_free(struct sock *sk, struct sk_msg *msg)
{
	return __sk_msg_free(sk, msg, msg->sg.start, true);
}