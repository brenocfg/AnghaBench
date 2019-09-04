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
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ADM8211_SRAM_SIZE ; 
 int /*<<< orphan*/  WEPCTL ; 
 int /*<<< orphan*/  adm8211_write_sram (struct ieee80211_hw*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adm8211_clear_sram(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	u32 reg = ADM8211_CSR_READ(WEPCTL);
	unsigned int addr;

	for (addr = 0; addr < ADM8211_SRAM_SIZE; addr++)
		adm8211_write_sram(dev, addr, 0);

	ADM8211_CSR_WRITE(WEPCTL, reg);
}