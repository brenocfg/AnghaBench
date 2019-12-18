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
struct TYPE_2__ {scalar_t__ dim; int /*<<< orphan*/  index; } ;
struct xt_set_info_match_v1 {TYPE_1__ match_set; } ;
struct xt_mtchk_param {int /*<<< orphan*/  net; struct xt_set_info_match_v1* matchinfo; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 int ENOENT ; 
 int ERANGE ; 
 scalar_t__ IPSET_DIM_MAX ; 
 scalar_t__ IPSET_INVALID_ID ; 
 scalar_t__ ip_set_nfnl_get_byindex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_nfnl_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 

__attribute__((used)) static int
set_match_v1_checkentry(const struct xt_mtchk_param *par)
{
	struct xt_set_info_match_v1 *info = par->matchinfo;
	ip_set_id_t index;

	index = ip_set_nfnl_get_byindex(par->net, info->match_set.index);

	if (index == IPSET_INVALID_ID) {
		pr_info_ratelimited("Cannot find set identified by id %u to match\n",
				    info->match_set.index);
		return -ENOENT;
	}
	if (info->match_set.dim > IPSET_DIM_MAX) {
		pr_info_ratelimited("set match dimension is over the limit!\n");
		ip_set_nfnl_put(par->net, info->match_set.index);
		return -ERANGE;
	}

	return 0;
}