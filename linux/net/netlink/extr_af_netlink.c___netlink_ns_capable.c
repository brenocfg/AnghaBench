#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct user_namespace {int dummy; } ;
struct netlink_skb_parms {int flags; TYPE_2__* sk; } ;
struct TYPE_4__ {TYPE_1__* sk_socket; } ;
struct TYPE_3__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int NETLINK_SKB_DST ; 
 scalar_t__ file_ns_capable (int /*<<< orphan*/ ,struct user_namespace*,int) ; 
 scalar_t__ ns_capable (struct user_namespace*,int) ; 

bool __netlink_ns_capable(const struct netlink_skb_parms *nsp,
			struct user_namespace *user_ns, int cap)
{
	return ((nsp->flags & NETLINK_SKB_DST) ||
		file_ns_capable(nsp->sk->sk_socket->file, user_ns, cap)) &&
		ns_capable(user_ns, cap);
}