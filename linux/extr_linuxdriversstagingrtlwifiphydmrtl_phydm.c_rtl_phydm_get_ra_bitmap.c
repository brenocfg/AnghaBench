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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;
typedef  enum rf_type { ____Placeholder_rf_type } rf_type ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int /*<<< orphan*/  phydm_update_hal_ra_mask (struct phy_dm_struct*,int,int,int,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_get_ra_bitmap(struct rtl_priv *rtlpriv,
				    enum wireless_mode wireless_mode,
				    enum rf_type rf_type,
				    enum ht_channel_width bw,
				    u8 tx_rate_level, /* 0~6 */
				    u32 *tx_bitmap_msb,
				    u32 *tx_bitmap_lsb)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	const u8 mimo_ps_enable = 0;
	const u8 disable_cck_rate = 0;

	phydm_update_hal_ra_mask(dm, wireless_mode, rf_type, bw, mimo_ps_enable,
				 disable_cck_rate, tx_bitmap_msb, tx_bitmap_lsb,
				 tx_rate_level);

	return true;
}