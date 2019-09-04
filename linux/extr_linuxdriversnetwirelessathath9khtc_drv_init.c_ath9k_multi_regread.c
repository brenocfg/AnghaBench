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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  wmi; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  WMI ; 
 int /*<<< orphan*/  WMI_REG_READ_CMDID ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_wmi_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ath9k_multi_regread(void *hw_priv, u32 *addr,
				u32 *val, u16 count)
{
	struct ath_hw *ah = hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;
	__be32 tmpaddr[8];
	__be32 tmpval[8];
	int i, ret;

	for (i = 0; i < count; i++) {
		tmpaddr[i] = cpu_to_be32(addr[i]);
	}

	ret = ath9k_wmi_cmd(priv->wmi, WMI_REG_READ_CMDID,
			   (u8 *)tmpaddr , sizeof(u32) * count,
			   (u8 *)tmpval, sizeof(u32) * count,
			   100);
	if (unlikely(ret)) {
		ath_dbg(common, WMI,
			"Multiple REGISTER READ FAILED (count: %d)\n", count);
	}

	for (i = 0; i < count; i++) {
		val[i] = be32_to_cpu(tmpval[i]);
	}
}