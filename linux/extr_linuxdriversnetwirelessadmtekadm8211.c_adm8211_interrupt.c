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
typedef  int u32 ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct adm8211_priv* priv; } ;
struct adm8211_priv {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 int ADM8211_STSR_AISS ; 
 int ADM8211_STSR_ATIME ; 
 int ADM8211_STSR_ATIMTC ; 
 int ADM8211_STSR_BCNTC ; 
 int ADM8211_STSR_FBE ; 
 int ADM8211_STSR_GPINT ; 
 int ADM8211_STSR_GPTT ; 
 int ADM8211_STSR_NISS ; 
 int ADM8211_STSR_PCF ; 
 int ADM8211_STSR_RCI ; 
 int ADM8211_STSR_RDU ; 
 int ADM8211_STSR_REIS ; 
 int ADM8211_STSR_RPS ; 
 int ADM8211_STSR_SQL ; 
 int ADM8211_STSR_TCI ; 
 int ADM8211_STSR_TEIS ; 
 int ADM8211_STSR_TPS ; 
 int ADM8211_STSR_TSCZ ; 
 int ADM8211_STSR_TSFTF ; 
 int ADM8211_STSR_TUF ; 
 int ADM8211_STSR_WEPTD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  STSR ; 
 int /*<<< orphan*/  adm8211_interrupt_rci (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  adm8211_interrupt_tci (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static irqreturn_t adm8211_interrupt(int irq, void *dev_id)
{
#define ADM8211_INT(x)						\
do {								\
	if (unlikely(stsr & ADM8211_STSR_ ## x))		\
		wiphy_debug(dev->wiphy, "%s\n", #x);		\
} while (0)

	struct ieee80211_hw *dev = dev_id;
	struct adm8211_priv *priv = dev->priv;
	u32 stsr = ADM8211_CSR_READ(STSR);
	ADM8211_CSR_WRITE(STSR, stsr);
	if (stsr == 0xffffffff)
		return IRQ_HANDLED;

	if (!(stsr & (ADM8211_STSR_NISS | ADM8211_STSR_AISS)))
		return IRQ_HANDLED;

	if (stsr & ADM8211_STSR_RCI)
		adm8211_interrupt_rci(dev);
	if (stsr & ADM8211_STSR_TCI)
		adm8211_interrupt_tci(dev);

	ADM8211_INT(PCF);
	ADM8211_INT(BCNTC);
	ADM8211_INT(GPINT);
	ADM8211_INT(ATIMTC);
	ADM8211_INT(TSFTF);
	ADM8211_INT(TSCZ);
	ADM8211_INT(SQL);
	ADM8211_INT(WEPTD);
	ADM8211_INT(ATIME);
	ADM8211_INT(TEIS);
	ADM8211_INT(FBE);
	ADM8211_INT(REIS);
	ADM8211_INT(GPTT);
	ADM8211_INT(RPS);
	ADM8211_INT(RDU);
	ADM8211_INT(TUF);
	ADM8211_INT(TPS);

	return IRQ_HANDLED;

#undef ADM8211_INT
}