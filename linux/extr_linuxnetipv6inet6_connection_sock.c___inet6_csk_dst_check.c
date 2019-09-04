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
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct dst_entry *__inet6_csk_dst_check(struct sock *sk, u32 cookie)
{
	return __sk_dst_check(sk, cookie);
}