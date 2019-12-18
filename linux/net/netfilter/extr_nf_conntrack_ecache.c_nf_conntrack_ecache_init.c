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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int __IPCT_MAX ; 
 int /*<<< orphan*/  event_extend ; 
 int nf_ct_extend_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int nf_conntrack_ecache_init(void)
{
	int ret = nf_ct_extend_register(&event_extend);
	if (ret < 0)
		pr_err("Unable to register event extension\n");

	BUILD_BUG_ON(__IPCT_MAX >= 16);	/* ctmask, missed use u16 */

	return ret;
}