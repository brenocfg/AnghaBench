#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct rtl8180_priv {int rf_type; int csthreshold; scalar_t__ chip_family; int rfparam; int antenna_diversity_en; int antenna_diversity_default; int xtal_out; int xtal_in; int xtal_cal; int thermal_meter_val; int thermal_meter_en; TYPE_2__* map; int /*<<< orphan*/  anaparam; TYPE_1__* channels; scalar_t__ mac_addr; } ;
struct eeprom_93cx6 {int /*<<< orphan*/  width; int /*<<< orphan*/  register_write; int /*<<< orphan*/  register_read; struct rtl8180_priv* data; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  EEPROM_CMD; int /*<<< orphan*/  RX_CONF; } ;
struct TYPE_3__ {int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C46 ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C66 ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8180 ; 
 scalar_t__ RTL818X_CHIP_FAMILY_RTL8187SE ; 
 int /*<<< orphan*/  RTL818X_EEPROM_CMD_NORMAL ; 
 int /*<<< orphan*/  RTL818X_EEPROM_CMD_PROGRAM ; 
 int /*<<< orphan*/  eeprom_93cx6_multiread (struct eeprom_93cx6*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eeprom_93cx6_read (struct eeprom_93cx6*,int,int*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_eeprom_register_read ; 
 int /*<<< orphan*/  rtl8180_eeprom_register_write ; 
 int rtl818x_ioread32 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_ioread8 (struct rtl8180_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8180_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl8180_eeprom_read(struct rtl8180_priv *priv)
{
	struct eeprom_93cx6 eeprom;
	int eeprom_cck_table_adr;
	u16 eeprom_val;
	int i;

	eeprom.data = priv;
	eeprom.register_read = rtl8180_eeprom_register_read;
	eeprom.register_write = rtl8180_eeprom_register_write;
	if (rtl818x_ioread32(priv, &priv->map->RX_CONF) & (1 << 6))
		eeprom.width = PCI_EEPROM_WIDTH_93C66;
	else
		eeprom.width = PCI_EEPROM_WIDTH_93C46;

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			RTL818X_EEPROM_CMD_PROGRAM);
	rtl818x_ioread8(priv, &priv->map->EEPROM_CMD);
	udelay(10);

	eeprom_93cx6_read(&eeprom, 0x06, &eeprom_val);
	eeprom_val &= 0xFF;
	priv->rf_type = eeprom_val;

	eeprom_93cx6_read(&eeprom, 0x17, &eeprom_val);
	priv->csthreshold = eeprom_val >> 8;

	eeprom_93cx6_multiread(&eeprom, 0x7, (__le16 *)priv->mac_addr, 3);

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE)
		eeprom_cck_table_adr = 0x30;
	else
		eeprom_cck_table_adr = 0x10;

	/* CCK TX power */
	for (i = 0; i < 14; i += 2) {
		u16 txpwr;
		eeprom_93cx6_read(&eeprom, eeprom_cck_table_adr + (i >> 1),
				&txpwr);
		priv->channels[i].hw_value = txpwr & 0xFF;
		priv->channels[i + 1].hw_value = txpwr >> 8;
	}

	/* OFDM TX power */
	if (priv->chip_family != RTL818X_CHIP_FAMILY_RTL8180) {
		for (i = 0; i < 14; i += 2) {
			u16 txpwr;
			eeprom_93cx6_read(&eeprom, 0x20 + (i >> 1), &txpwr);
			priv->channels[i].hw_value |= (txpwr & 0xFF) << 8;
			priv->channels[i + 1].hw_value |= txpwr & 0xFF00;
		}
	}

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8180) {
		__le32 anaparam;
		eeprom_93cx6_multiread(&eeprom, 0xD, (__le16 *)&anaparam, 2);
		priv->anaparam = le32_to_cpu(anaparam);
		eeprom_93cx6_read(&eeprom, 0x19, &priv->rfparam);
	}

	if (priv->chip_family == RTL818X_CHIP_FAMILY_RTL8187SE) {
		eeprom_93cx6_read(&eeprom, 0x3F, &eeprom_val);
		priv->antenna_diversity_en = !!(eeprom_val & 0x100);
		priv->antenna_diversity_default = (eeprom_val & 0xC00) == 0x400;

		eeprom_93cx6_read(&eeprom, 0x7C, &eeprom_val);
		priv->xtal_out = eeprom_val & 0xF;
		priv->xtal_in = (eeprom_val & 0xF0) >> 4;
		priv->xtal_cal = !!(eeprom_val & 0x1000);
		priv->thermal_meter_val = (eeprom_val & 0xF00) >> 8;
		priv->thermal_meter_en = !!(eeprom_val & 0x2000);
	}

	rtl818x_iowrite8(priv, &priv->map->EEPROM_CMD,
			RTL818X_EEPROM_CMD_NORMAL);
}