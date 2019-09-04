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
struct xt_mtchk_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int state_mt_check(const struct xt_mtchk_param *par)
{
	int ret;

	ret = nf_ct_netns_get(par->net, par->family);
	if (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	return ret;
}