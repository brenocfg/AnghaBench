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
 int /*<<< orphan*/  nf_ct_extend_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_extend ; 

void nf_conntrack_timeout_fini(void)
{
	nf_ct_extend_unregister(&timeout_extend);
}