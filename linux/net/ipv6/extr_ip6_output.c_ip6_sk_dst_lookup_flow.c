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
struct in6_addr {int dummy; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_clone (struct dst_entry*) ; 
 TYPE_1__* inet6_sk (struct sock*) ; 
 struct dst_entry* ip6_dst_lookup_flow (struct sock*,struct flowi6*,struct in6_addr const*) ; 
 struct dst_entry* ip6_sk_dst_check (struct sock*,struct dst_entry*,struct flowi6*) ; 
 int /*<<< orphan*/  ip6_sk_dst_store_flow (struct sock*,int /*<<< orphan*/ ,struct flowi6*) ; 
 struct dst_entry* sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 

struct dst_entry *ip6_sk_dst_lookup_flow(struct sock *sk, struct flowi6 *fl6,
					 const struct in6_addr *final_dst,
					 bool connected)
{
	struct dst_entry *dst = sk_dst_check(sk, inet6_sk(sk)->dst_cookie);

	dst = ip6_sk_dst_check(sk, dst, fl6);
	if (dst)
		return dst;

	dst = ip6_dst_lookup_flow(sk, fl6, final_dst);
	if (connected && !IS_ERR(dst))
		ip6_sk_dst_store_flow(sk, dst_clone(dst), fl6);

	return dst;
}