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
struct sock {int /*<<< orphan*/  sk_destruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  pn_destruct ; 

__attribute__((used)) static int pn_init(struct sock *sk)
{
	sk->sk_destruct = pn_destruct;
	return 0;
}