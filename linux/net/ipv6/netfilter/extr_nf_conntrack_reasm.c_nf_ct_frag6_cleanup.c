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

/* Variables and functions */
 int /*<<< orphan*/  inet_frags_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_net_ops ; 
 int /*<<< orphan*/  nf_frags ; 
 int /*<<< orphan*/  unregister_pernet_subsys (int /*<<< orphan*/ *) ; 

void nf_ct_frag6_cleanup(void)
{
	unregister_pernet_subsys(&nf_ct_net_ops);
	inet_frags_fini(&nf_frags);
}