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
typedef  int u8 ;
typedef  size_t u32 ;
struct mwifiex_private {scalar_t__* bitmap_rates; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 

u8
mwifiex_is_rate_auto(struct mwifiex_private *priv)
{
	u32 i;
	int rate_num = 0;

	for (i = 0; i < ARRAY_SIZE(priv->bitmap_rates); i++)
		if (priv->bitmap_rates[i])
			rate_num++;

	if (rate_num > 1)
		return true;
	else
		return false;
}