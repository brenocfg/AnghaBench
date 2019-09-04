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
struct TYPE_2__ {int /*<<< orphan*/  lps_change_work; int /*<<< orphan*/  irq_prepare_bcn_tasklet; int /*<<< orphan*/  irq_tasklet; } ;
struct rtl_priv {TYPE_1__ works; } ;
struct rtl_pci {int up_first_time; int being_init_adapter; int /*<<< orphan*/  acm_method; struct pci_dev* pdev; } ;
struct rtl_mac {int beacon_interval; int current_ampdu_density; int current_ampdu_factor; int retry_short; int retry_long; scalar_t__ max_mss_density; scalar_t__ min_space_cfg; } ;
struct rtl_hal {struct ieee80211_hw* hw; } ;
struct pci_dev {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACMWAY2_SW ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_pci_init_trx_var (struct ieee80211_hw*) ; 
 scalar_t__ _rtl_pci_irq_tasklet ; 
 scalar_t__ _rtl_pci_prepare_bcn_tasklet ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_lps_change_work_callback ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

__attribute__((used)) static void _rtl_pci_init_struct(struct ieee80211_hw *hw,
				 struct pci_dev *pdev)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	rtlpci->up_first_time = true;
	rtlpci->being_init_adapter = false;

	rtlhal->hw = hw;
	rtlpci->pdev = pdev;

	/*Tx/Rx related var */
	_rtl_pci_init_trx_var(hw);

	/*IBSS*/
	mac->beacon_interval = 100;

	/*AMPDU*/
	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;
	/*set sane AMPDU defaults */
	mac->current_ampdu_density = 7;
	mac->current_ampdu_factor = 3;

	/*Retry Limit*/
	mac->retry_short = 7;
	mac->retry_long = 7;

	/*QOS*/
	rtlpci->acm_method = EACMWAY2_SW;

	/*task */
	tasklet_init(&rtlpriv->works.irq_tasklet,
		     (void (*)(unsigned long))_rtl_pci_irq_tasklet,
		     (unsigned long)hw);
	tasklet_init(&rtlpriv->works.irq_prepare_bcn_tasklet,
		     (void (*)(unsigned long))_rtl_pci_prepare_bcn_tasklet,
		     (unsigned long)hw);
	INIT_WORK(&rtlpriv->works.lps_change_work,
		  rtl_lps_change_work_callback);
}