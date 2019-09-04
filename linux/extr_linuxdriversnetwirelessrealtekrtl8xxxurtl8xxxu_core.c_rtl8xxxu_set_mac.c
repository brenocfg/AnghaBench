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
typedef  scalar_t__ u16 ;
struct rtl8xxxu_priv {int /*<<< orphan*/ * mac_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ REG_MACID ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8xxxu_set_mac(struct rtl8xxxu_priv *priv)
{
	int i;
	u16 reg;

	reg = REG_MACID;

	for (i = 0; i < ETH_ALEN; i++)
		rtl8xxxu_write8(priv, reg + i, priv->mac_addr[i]);

	return 0;
}