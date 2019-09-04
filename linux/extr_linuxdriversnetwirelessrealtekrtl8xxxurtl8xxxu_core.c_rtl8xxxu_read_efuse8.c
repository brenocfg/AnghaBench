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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 scalar_t__ REG_EFUSE_CTRL ; 
 int RTL8XXXU_MAX_REG_POLL ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,scalar_t__) ; 
 int rtl8xxxu_read8 (struct rtl8xxxu_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rtl8xxxu_read_efuse8(struct rtl8xxxu_priv *priv, u16 offset, u8 *data)
{
	int i;
	u8 val8;
	u32 val32;

	/* Write Address */
	rtl8xxxu_write8(priv, REG_EFUSE_CTRL + 1, offset & 0xff);
	val8 = rtl8xxxu_read8(priv, REG_EFUSE_CTRL + 2);
	val8 &= 0xfc;
	val8 |= (offset >> 8) & 0x03;
	rtl8xxxu_write8(priv, REG_EFUSE_CTRL + 2, val8);

	val8 = rtl8xxxu_read8(priv, REG_EFUSE_CTRL + 3);
	rtl8xxxu_write8(priv, REG_EFUSE_CTRL + 3, val8 & 0x7f);

	/* Poll for data read */
	val32 = rtl8xxxu_read32(priv, REG_EFUSE_CTRL);
	for (i = 0; i < RTL8XXXU_MAX_REG_POLL; i++) {
		val32 = rtl8xxxu_read32(priv, REG_EFUSE_CTRL);
		if (val32 & BIT(31))
			break;
	}

	if (i == RTL8XXXU_MAX_REG_POLL)
		return -EIO;

	udelay(50);
	val32 = rtl8xxxu_read32(priv, REG_EFUSE_CTRL);

	*data = val32 & 0xff;
	return 0;
}