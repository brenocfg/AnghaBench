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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_pmtu ) (struct dst_entry*,struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 struct dst_entry* inet6_csk_route_socket (struct sock*,struct flowi6*) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dst_entry *inet6_csk_update_pmtu(struct sock *sk, u32 mtu)
{
	struct flowi6 fl6;
	struct dst_entry *dst = inet6_csk_route_socket(sk, &fl6);

	if (IS_ERR(dst))
		return NULL;
	dst->ops->update_pmtu(dst, sk, NULL, mtu);

	dst = inet6_csk_route_socket(sk, &fl6);
	return IS_ERR(dst) ? NULL : dst;
}