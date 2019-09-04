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
 scalar_t__ phydm_c2H_content_parsing (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_c2h_content_parsing(struct rtl_priv *rtlpriv, u8 cmd_id,
					  u8 cmd_len, u8 *content)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	if (phydm_c2H_content_parsing(dm, cmd_id, cmd_len, content))
		return true;

	return false;
}