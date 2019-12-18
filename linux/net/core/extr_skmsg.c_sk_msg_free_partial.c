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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_msg_free_partial (struct sock*,struct sk_msg*,int /*<<< orphan*/ ,int) ; 

void sk_msg_free_partial(struct sock *sk, struct sk_msg *msg, u32 bytes)
{
	__sk_msg_free_partial(sk, msg, bytes, true);
}