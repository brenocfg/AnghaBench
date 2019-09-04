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
struct brcmstb_thermal_priv {int /*<<< orphan*/  thermal; scalar_t__ tmon_base; } ;

/* Variables and functions */
 scalar_t__ AVS_TMON_TEMP_INT_CODE ; 
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int avs_tmon_code_to_temp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avs_tmon_get_intr_temp(struct brcmstb_thermal_priv *priv)
{
	u32 val;

	val = __raw_readl(priv->tmon_base + AVS_TMON_TEMP_INT_CODE);
	return avs_tmon_code_to_temp(priv->thermal, val);
}