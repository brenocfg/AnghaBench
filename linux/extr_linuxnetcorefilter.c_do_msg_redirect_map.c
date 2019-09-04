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
struct sk_msg_buff {struct sock* sk_redir; } ;

/* Variables and functions */

struct sock *do_msg_redirect_map(struct sk_msg_buff *msg)
{
	return msg->sk_redir;
}