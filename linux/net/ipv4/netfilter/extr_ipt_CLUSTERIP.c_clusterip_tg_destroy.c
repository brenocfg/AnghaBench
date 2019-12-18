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
struct xt_tgdtor_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; struct ipt_clusterip_tgt_info* targinfo; } ;
struct ipt_clusterip_tgt_info {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  clusterip_config_entry_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterip_config_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clusterip_tg_destroy(const struct xt_tgdtor_param *par)
{
	const struct ipt_clusterip_tgt_info *cipinfo = par->targinfo;

	/* if no more entries are referencing the config, remove it
	 * from the list and destroy the proc entry */
	clusterip_config_entry_put(cipinfo->config);

	clusterip_config_put(cipinfo->config);

	nf_ct_netns_put(par->net, par->family);
}