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
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ABDA1 ; 
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BSSID0 ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adm8211_set_bssid(struct ieee80211_hw *dev, const u8 *bssid)
{
	struct adm8211_priv *priv = dev->priv;
	u32 reg;

	ADM8211_CSR_WRITE(BSSID0, le32_to_cpu(*(__le32 *)bssid));
	reg = ADM8211_CSR_READ(ABDA1);
	reg &= 0x0000ffff;
	reg |= (bssid[4] << 16) | (bssid[5] << 24);
	ADM8211_CSR_WRITE(ABDA1, reg);
}