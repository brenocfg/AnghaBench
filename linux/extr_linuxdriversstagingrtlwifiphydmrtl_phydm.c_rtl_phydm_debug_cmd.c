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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phydm_cmd (struct phy_dm_struct*,char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_debug_cmd(struct rtl_priv *rtlpriv, char *in, u32 in_len,
				char *out, u32 out_len)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);

	phydm_cmd(dm, in, in_len, 1, out, out_len);

	return true;
}