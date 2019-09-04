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
struct phy_dm_struct {scalar_t__ adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void odm_write_1byte(struct phy_dm_struct *dm, u32 reg_addr, u8 data)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	rtl_write_byte(rtlpriv, reg_addr, data);
}