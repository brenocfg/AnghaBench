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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  wmi; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int EIO ; 
 int /*<<< orphan*/  WMI ; 
 int /*<<< orphan*/  WMI_REG_READ_CMDID ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int ath9k_wmi_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int ath9k_regread(void *hw_priv, u32 reg_offset)
{
	struct ath_hw *ah = hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;
	__be32 val, reg = cpu_to_be32(reg_offset);
	int r;

	r = ath9k_wmi_cmd(priv->wmi, WMI_REG_READ_CMDID,
			  (u8 *) &reg, sizeof(reg),
			  (u8 *) &val, sizeof(val),
			  100);
	if (unlikely(r)) {
		ath_dbg(common, WMI, "REGISTER READ FAILED: (0x%04x, %d)\n",
			reg_offset, r);
		return -EIO;
	}

	return be32_to_cpu(val);
}