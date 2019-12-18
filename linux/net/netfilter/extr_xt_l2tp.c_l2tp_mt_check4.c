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
struct xt_mtchk_param {struct ipt_entry* entryinfo; struct xt_l2tp_info* matchinfo; } ;
struct xt_l2tp_info {int version; } ;
struct ipt_ip {scalar_t__ proto; } ;
struct ipt_entry {struct ipt_ip ip; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPPROTO_L2TP ; 
 scalar_t__ IPPROTO_UDP ; 
 int l2tp_mt_check (struct xt_mtchk_param const*) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*) ; 

__attribute__((used)) static int l2tp_mt_check4(const struct xt_mtchk_param *par)
{
	const struct xt_l2tp_info *info = par->matchinfo;
	const struct ipt_entry *e = par->entryinfo;
	const struct ipt_ip *ip = &e->ip;
	int ret;

	ret = l2tp_mt_check(par);
	if (ret != 0)
		return ret;

	if ((ip->proto != IPPROTO_UDP) &&
	    (ip->proto != IPPROTO_L2TP)) {
		pr_info_ratelimited("missing protocol rule (udp|l2tpip)\n");
		return -EINVAL;
	}

	if ((ip->proto == IPPROTO_L2TP) &&
	    (info->version == 2)) {
		pr_info_ratelimited("v2 doesn't support IP mode\n");
		return -EINVAL;
	}

	return 0;
}