#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl8180_priv {TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  CONFIG3; int /*<<< orphan*/  ANAPARAM2; } ;

/* Variables and functions */
 int RTL818X_CONFIG3_ANAPARAM_WRITE ; 
 int RTL818X_EEPROM_CMD_CONFIG ; 
 int RTL818X_EEPROM_CMD_NORMAL ; 
 int rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite32 (struct rtl8180_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int) ; 

void rtl8180_set_anaparam2(struct rtl8180_priv *priv, u32 anaparam2)
{
	u8 reg;

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_CONFIG);

	reg = rtl818x_ioread8(priv, &priv->map->CONFIG3);
	rtl818x_iowrite8(priv, &priv->map->CONFIG3,
		 reg | RTL818X_CONFIG3_ANAPARAM_WRITE);

	rtl818x_iowrite32(priv, &priv->map->ANAPARAM2, anaparam2);

	rtl818x_iowrite8(priv, &priv->map->CONFIG3,
		 reg & ~RTL818X_CONFIG3_ANAPARAM_WRITE);

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			 RTL818X_EEPROM_CMD_NORMAL);
}