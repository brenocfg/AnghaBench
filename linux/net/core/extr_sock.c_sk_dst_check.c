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
struct dst_entry {TYPE_1__* ops; scalar_t__ obsolete; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* sk_dst_get (struct sock*) ; 
 int /*<<< orphan*/  sk_dst_reset (struct sock*) ; 
 int /*<<< orphan*/ * stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

struct dst_entry *sk_dst_check(struct sock *sk, u32 cookie)
{
	struct dst_entry *dst = sk_dst_get(sk);

	if (dst && dst->obsolete && dst->ops->check(dst, cookie) == NULL) {
		sk_dst_reset(sk);
		dst_release(dst);
		return NULL;
	}

	return dst;
}