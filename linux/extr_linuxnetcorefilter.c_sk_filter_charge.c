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
struct sk_filter {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_filter_charge (struct sock*,struct sk_filter*) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_filter_release (struct sk_filter*) ; 

bool sk_filter_charge(struct sock *sk, struct sk_filter *fp)
{
	if (!refcount_inc_not_zero(&fp->refcnt))
		return false;

	if (!__sk_filter_charge(sk, fp)) {
		sk_filter_release(fp);
		return false;
	}
	return true;
}