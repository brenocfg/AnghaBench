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
struct xt_mtchk_param {scalar_t__ family; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,scalar_t__) ; 

__attribute__((used)) static int ipvs_mt_check(const struct xt_mtchk_param *par)
{
	if (par->family != NFPROTO_IPV4
#ifdef CONFIG_IP_VS_IPV6
	    && par->family != NFPROTO_IPV6
#endif
		) {
		pr_info_ratelimited("protocol family %u not supported\n",
				    par->family);
		return -EINVAL;
	}

	return 0;
}