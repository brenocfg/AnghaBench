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
struct iwl_cfg {int dummy; } ;
struct TYPE_2__ {int disable_11n; } ;

/* Variables and functions */
 int IWL_DISABLE_HT_RXAGG ; 
 TYPE_1__ iwlwifi_mod_params ; 

__attribute__((used)) static inline bool iwl_enable_rx_ampdu(const struct iwl_cfg *cfg)
{
	if (iwlwifi_mod_params.disable_11n & IWL_DISABLE_HT_RXAGG)
		return false;
	return true;
}