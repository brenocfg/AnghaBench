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
typedef  int u32 ;
struct rtl8xxxu_priv {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AUTO_LLT_INIT_LLT ; 
 int EBUSY ; 
 int /*<<< orphan*/  REG_AUTO_LLT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int rtl8xxxu_auto_llt_table(struct rtl8xxxu_priv *priv)
{
	u32 val32;
	int ret = 0;
	int i;

	val32 = rtl8xxxu_read32(priv, REG_AUTO_LLT);
	val32 |= AUTO_LLT_INIT_LLT;
	rtl8xxxu_write32(priv, REG_AUTO_LLT, val32);

	for (i = 500; i; i--) {
		val32 = rtl8xxxu_read32(priv, REG_AUTO_LLT);
		if (!(val32 & AUTO_LLT_INIT_LLT))
			break;
		usleep_range(2, 4);
	}

	if (!i) {
		ret = -EBUSY;
		dev_warn(&priv->udev->dev, "LLT table init failed\n");
	}

	return ret;
}