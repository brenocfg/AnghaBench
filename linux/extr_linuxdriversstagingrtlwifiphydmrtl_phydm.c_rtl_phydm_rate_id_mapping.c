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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;
typedef  enum rf_type { ____Placeholder_rf_type } rf_type ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 int /*<<< orphan*/  phydm_rate_id_mapping (struct phy_dm_struct*,int,int,int) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static u8 rtl_phydm_rate_id_mapping(struct rtl_priv *rtlpriv,
				    enum wireless_mode wireless_mode,
				    enum rf_type rf_type,
				    enum ht_channel_width bw)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	return phydm_rate_id_mapping(dm, wireless_mode, rf_type, bw);
}