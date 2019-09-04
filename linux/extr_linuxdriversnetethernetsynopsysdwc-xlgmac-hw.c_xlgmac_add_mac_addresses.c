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
struct TYPE_2__ {scalar_t__ hash_table_size; } ;
struct xlgmac_pdata {TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  xlgmac_set_mac_addn_addrs (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_set_mac_hash_table (struct xlgmac_pdata*) ; 

__attribute__((used)) static int xlgmac_add_mac_addresses(struct xlgmac_pdata *pdata)
{
	if (pdata->hw_feat.hash_table_size)
		xlgmac_set_mac_hash_table(pdata);
	else
		xlgmac_set_mac_addn_addrs(pdata);

	return 0;
}