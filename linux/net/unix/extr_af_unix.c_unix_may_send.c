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
 scalar_t__ unix_our_peer (struct sock*,struct sock*) ; 
 int /*<<< orphan*/ * unix_peer (struct sock*) ; 

__attribute__((used)) static inline int unix_may_send(struct sock *sk, struct sock *osk)
{
	return unix_peer(osk) == NULL || unix_our_peer(sk, osk);
}