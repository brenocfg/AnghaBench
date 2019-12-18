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
struct sock {TYPE_1__* sk_memcg; } ;
struct TYPE_2__ {int /*<<< orphan*/  css; } ;

/* Variables and functions */
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 

void mem_cgroup_sk_free(struct sock *sk)
{
	if (sk->sk_memcg)
		css_put(&sk->sk_memcg->css);
}