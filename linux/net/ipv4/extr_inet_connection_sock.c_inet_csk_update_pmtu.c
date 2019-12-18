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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fl; } ;
struct inet_sock {TYPE_1__ cork; } ;
struct dst_entry {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_pmtu ) (struct dst_entry*,struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct dst_entry* __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 struct dst_entry* inet_csk_rebuild_route (struct sock*,int /*<<< orphan*/ *) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct dst_entry *inet_csk_update_pmtu(struct sock *sk, u32 mtu)
{
	struct dst_entry *dst = __sk_dst_check(sk, 0);
	struct inet_sock *inet = inet_sk(sk);

	if (!dst) {
		dst = inet_csk_rebuild_route(sk, &inet->cork.fl);
		if (!dst)
			goto out;
	}
	dst->ops->update_pmtu(dst, sk, NULL, mtu);

	dst = __sk_dst_check(sk, 0);
	if (!dst)
		dst = inet_csk_rebuild_route(sk, &inet->cork.fl);
out:
	return dst;
}