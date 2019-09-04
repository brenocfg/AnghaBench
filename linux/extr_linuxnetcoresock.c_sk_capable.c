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

/* Variables and functions */
 int /*<<< orphan*/  init_user_ns ; 
 int sk_ns_capable (struct sock const*,int /*<<< orphan*/ *,int) ; 

bool sk_capable(const struct sock *sk, int cap)
{
	return sk_ns_capable(sk, &init_user_ns, cap);
}