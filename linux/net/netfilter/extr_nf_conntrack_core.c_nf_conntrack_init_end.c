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
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_ct_attach ; 
 int /*<<< orphan*/ * nf_conntrack_attach ; 
 int /*<<< orphan*/  nf_conntrack_hook ; 
 int /*<<< orphan*/  nf_ct_hook ; 

void nf_conntrack_init_end(void)
{
	/* For use by REJECT target */
	RCU_INIT_POINTER(ip_ct_attach, nf_conntrack_attach);
	RCU_INIT_POINTER(nf_ct_hook, &nf_conntrack_hook);
}