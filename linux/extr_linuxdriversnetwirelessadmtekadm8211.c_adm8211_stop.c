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
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {TYPE_1__* pdev; scalar_t__ nar; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  NAR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  adm8211_free_rings (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ieee80211_hw*) ; 

__attribute__((used)) static void adm8211_stop(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;

	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->nar = 0;
	ADM8211_CSR_WRITE(NAR, 0);
	ADM8211_CSR_WRITE(IER, 0);
	ADM8211_CSR_READ(NAR);

	free_irq(priv->pdev->irq, dev);

	adm8211_free_rings(dev);
}