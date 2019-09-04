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
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int LLT_OP_INACTIVE ; 
 int LLT_OP_MASK ; 
 int LLT_OP_WRITE ; 
 int /*<<< orphan*/  REG_LLT_INIT ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl8xxxu_llt_write(struct rtl8xxxu_priv *priv, u8 address, u8 data)
{
	int ret = -EBUSY;
	int count = 0;
	u32 value;

	value = LLT_OP_WRITE | address << 8 | data;

	rtl8xxxu_write32(priv, REG_LLT_INIT, value);

	do {
		value = rtl8xxxu_read32(priv, REG_LLT_INIT);
		if ((value & LLT_OP_MASK) == LLT_OP_INACTIVE) {
			ret = 0;
			break;
		}
	} while (count++ < 20);

	return ret;
}