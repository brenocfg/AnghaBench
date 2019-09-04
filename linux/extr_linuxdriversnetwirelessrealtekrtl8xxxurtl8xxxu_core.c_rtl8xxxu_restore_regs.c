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
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

void rtl8xxxu_restore_regs(struct rtl8xxxu_priv *priv, const u32 *regs,
			   u32 *backup, int count)
{
	int i;

	for (i = 0; i < count; i++)
		rtl8xxxu_write32(priv, regs[i], backup[i]);
}