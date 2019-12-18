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
typedef  int /*<<< orphan*/  u32 ;
struct seg6_pernet_data {int /*<<< orphan*/  hmac_infos; } ;
struct seg6_hmac_info {int /*<<< orphan*/  node; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct seg6_hmac_info* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rht_params ; 
 int /*<<< orphan*/  seg6_hinfo_release (struct seg6_hmac_info*) ; 
 struct seg6_pernet_data* seg6_pernet (struct net*) ; 

int seg6_hmac_info_del(struct net *net, u32 key)
{
	struct seg6_pernet_data *sdata = seg6_pernet(net);
	struct seg6_hmac_info *hinfo;
	int err = -ENOENT;

	hinfo = rhashtable_lookup_fast(&sdata->hmac_infos, &key, rht_params);
	if (!hinfo)
		goto out;

	err = rhashtable_remove_fast(&sdata->hmac_infos, &hinfo->node,
				     rht_params);
	if (err)
		goto out;

	seg6_hinfo_release(hinfo);

out:
	return err;
}