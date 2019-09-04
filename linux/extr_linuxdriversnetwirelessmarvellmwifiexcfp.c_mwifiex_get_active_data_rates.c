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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  num_of_rates; int /*<<< orphan*/  data_rates; } ;
struct mwifiex_private {TYPE_1__ curr_bss_params; int /*<<< orphan*/  media_connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_copy_rates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_get_supported_rates (struct mwifiex_private*,int /*<<< orphan*/ *) ; 

u32 mwifiex_get_active_data_rates(struct mwifiex_private *priv, u8 *rates)
{
	if (!priv->media_connected)
		return mwifiex_get_supported_rates(priv, rates);
	else
		return mwifiex_copy_rates(rates, 0,
					  priv->curr_bss_params.data_rates,
					  priv->curr_bss_params.num_of_rates);
}