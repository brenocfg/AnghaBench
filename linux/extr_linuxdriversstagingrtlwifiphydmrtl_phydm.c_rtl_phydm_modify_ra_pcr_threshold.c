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

/* Variables and functions */
 int /*<<< orphan*/  phydm_modify_RA_PCR_threshold (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_modify_ra_pcr_threshold(struct rtl_priv *rtlpriv,
					      u8 ra_offset_direction,
					      u8 ra_threshold_offset)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	phydm_modify_RA_PCR_threshold(dm, ra_offset_direction,
				      ra_threshold_offset);

	return true;
}