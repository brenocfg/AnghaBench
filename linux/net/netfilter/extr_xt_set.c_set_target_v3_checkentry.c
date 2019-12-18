#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {int hook_mask; int /*<<< orphan*/  net; int /*<<< orphan*/  table; struct xt_set_info_target_v3* targinfo; } ;
struct TYPE_6__ {scalar_t__ index; scalar_t__ dim; } ;
struct TYPE_5__ {scalar_t__ index; scalar_t__ dim; } ;
struct TYPE_4__ {scalar_t__ index; scalar_t__ dim; } ;
struct xt_set_info_target_v3 {int flags; TYPE_3__ add_set; TYPE_2__ del_set; TYPE_1__ map_set; } ;
typedef  scalar_t__ ip_set_id_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ERANGE ; 
 scalar_t__ IPSET_DIM_MAX ; 
 int IPSET_FLAG_MAP_SKBPRIO ; 
 int IPSET_FLAG_MAP_SKBQUEUE ; 
 scalar_t__ IPSET_INVALID_ID ; 
 int NF_INET_FORWARD ; 
 int NF_INET_LOCAL_OUT ; 
 int NF_INET_POST_ROUTING ; 
 scalar_t__ ip_set_nfnl_get_byindex (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ip_set_nfnl_put (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
set_target_v3_checkentry(const struct xt_tgchk_param *par)
{
	const struct xt_set_info_target_v3 *info = par->targinfo;
	ip_set_id_t index;
	int ret = 0;

	if (info->add_set.index != IPSET_INVALID_ID) {
		index = ip_set_nfnl_get_byindex(par->net,
						info->add_set.index);
		if (index == IPSET_INVALID_ID) {
			pr_info_ratelimited("Cannot find add_set index %u as target\n",
					    info->add_set.index);
			return -ENOENT;
		}
	}

	if (info->del_set.index != IPSET_INVALID_ID) {
		index = ip_set_nfnl_get_byindex(par->net,
						info->del_set.index);
		if (index == IPSET_INVALID_ID) {
			pr_info_ratelimited("Cannot find del_set index %u as target\n",
					    info->del_set.index);
			ret = -ENOENT;
			goto cleanup_add;
		}
	}

	if (info->map_set.index != IPSET_INVALID_ID) {
		if (strncmp(par->table, "mangle", 7)) {
			pr_info_ratelimited("--map-set only usable from mangle table\n");
			ret = -EINVAL;
			goto cleanup_del;
		}
		if (((info->flags & IPSET_FLAG_MAP_SKBPRIO) |
		     (info->flags & IPSET_FLAG_MAP_SKBQUEUE)) &&
		     (par->hook_mask & ~(1 << NF_INET_FORWARD |
					 1 << NF_INET_LOCAL_OUT |
					 1 << NF_INET_POST_ROUTING))) {
			pr_info_ratelimited("mapping of prio or/and queue is allowed only from OUTPUT/FORWARD/POSTROUTING chains\n");
			ret = -EINVAL;
			goto cleanup_del;
		}
		index = ip_set_nfnl_get_byindex(par->net,
						info->map_set.index);
		if (index == IPSET_INVALID_ID) {
			pr_info_ratelimited("Cannot find map_set index %u as target\n",
					    info->map_set.index);
			ret = -ENOENT;
			goto cleanup_del;
		}
	}

	if (info->add_set.dim > IPSET_DIM_MAX ||
	    info->del_set.dim > IPSET_DIM_MAX ||
	    info->map_set.dim > IPSET_DIM_MAX) {
		pr_info_ratelimited("SET target dimension over the limit!\n");
		ret = -ERANGE;
		goto cleanup_mark;
	}

	return 0;
cleanup_mark:
	if (info->map_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->map_set.index);
cleanup_del:
	if (info->del_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->del_set.index);
cleanup_add:
	if (info->add_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->add_set.index);
	return ret;
}