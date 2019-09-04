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
struct smc_pnetentry {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  kfree (struct smc_pnetentry*) ; 
 struct smc_pnetentry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int smc_pnet_enter (struct smc_pnetentry*) ; 
 int smc_pnet_fill_entry (struct net*,struct smc_pnetentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_pnet_add(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct smc_pnetentry *pnetelem;
	int rc;

	pnetelem = kzalloc(sizeof(*pnetelem), GFP_KERNEL);
	if (!pnetelem)
		return -ENOMEM;
	rc = smc_pnet_fill_entry(net, pnetelem, info->attrs);
	if (!rc)
		rc = smc_pnet_enter(pnetelem);
	if (rc) {
		kfree(pnetelem);
		return rc;
	}
	return rc;
}