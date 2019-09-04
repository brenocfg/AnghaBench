#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  rmw; int /*<<< orphan*/  rmw_flush; int /*<<< orphan*/  enable_rmw_buffer; int /*<<< orphan*/  write_flush; int /*<<< orphan*/  enable_write_buffer; int /*<<< orphan*/  write; int /*<<< orphan*/  multi_read; int /*<<< orphan*/  read; } ;
struct TYPE_5__ {int /*<<< orphan*/  usbdev; int /*<<< orphan*/  devid; } ;
struct ath_hw {TYPE_2__ reg_ops; int /*<<< orphan*/  ah_flags; TYPE_1__ hw_version; int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; } ;
struct ath_common {int btcoex_enabled; int cachelsz; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  debug_mask; struct ath9k_htc_priv* priv; int /*<<< orphan*/  hw; struct ath_hw* ah; int /*<<< orphan*/ * bus_ops; int /*<<< orphan*/ * ps_ops; TYPE_2__* ops; } ;
struct TYPE_8__ {int slottime; int /*<<< orphan*/ ** bslot; } ;
struct TYPE_7__ {int /*<<< orphan*/  cleanup_timer; int /*<<< orphan*/  tx_lock; } ;
struct ath9k_htc_priv {struct ath_hw* ah; TYPE_4__ beacon; TYPE_3__ tx; int /*<<< orphan*/  fatal_work; int /*<<< orphan*/  ps_work; int /*<<< orphan*/  ani_work; int /*<<< orphan*/  tx_failed_tasklet; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  htc_pm_lock; int /*<<< orphan*/  mutex; int /*<<< orphan*/  beacon_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_USE_EEPROM ; 
 int ATH9K_HTC_MAX_BCN_VIF ; 
 int /*<<< orphan*/  ATH_OP_INVALID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_cmn_init_channels_rates (struct ath_common*) ; 
 int /*<<< orphan*/  ath9k_cmn_init_crypto (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_debug ; 
 int /*<<< orphan*/  ath9k_enable_regwrite_buffer ; 
 int /*<<< orphan*/  ath9k_enable_rmw_buffer ; 
 int /*<<< orphan*/  ath9k_fatal_work ; 
 int /*<<< orphan*/  ath9k_htc_ani_work ; 
 int ath9k_htc_btcoex_enable ; 
 int /*<<< orphan*/  ath9k_htc_init_btcoex (struct ath9k_htc_priv*,char*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_ops ; 
 int /*<<< orphan*/  ath9k_htc_tx_cleanup_timer ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_deinit (struct ath_hw*) ; 
 int ath9k_hw_init (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_init_misc (struct ath9k_htc_priv*) ; 
 int ath9k_init_queues (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_multi_regread ; 
 int /*<<< orphan*/  ath9k_ps_work ; 
 int /*<<< orphan*/  ath9k_reg_rmw ; 
 int /*<<< orphan*/  ath9k_reg_rmw_flush ; 
 int /*<<< orphan*/  ath9k_regread ; 
 int /*<<< orphan*/  ath9k_regwrite ; 
 int /*<<< orphan*/  ath9k_regwrite_flush ; 
 int /*<<< orphan*/  ath9k_rx_tasklet ; 
 int /*<<< orphan*/  ath9k_tx_failed_tasklet ; 
 int /*<<< orphan*/  ath9k_usb_bus_ops ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int) ; 
 int /*<<< orphan*/  ath_read_cachesize (struct ath_common*,int*) ; 
 int /*<<< orphan*/  kfree (struct ath_hw*) ; 
 struct ath_hw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_init_priv(struct ath9k_htc_priv *priv,
			   u16 devid, char *product,
			   u32 drv_info)
{
	struct ath_hw *ah = NULL;
	struct ath_common *common;
	int i, ret = 0, csz = 0;

	ah = kzalloc(sizeof(struct ath_hw), GFP_KERNEL);
	if (!ah)
		return -ENOMEM;

	ah->dev = priv->dev;
	ah->hw = priv->hw;
	ah->hw_version.devid = devid;
	ah->hw_version.usbdev = drv_info;
	ah->ah_flags |= AH_USE_EEPROM;
	ah->reg_ops.read = ath9k_regread;
	ah->reg_ops.multi_read = ath9k_multi_regread;
	ah->reg_ops.write = ath9k_regwrite;
	ah->reg_ops.enable_write_buffer = ath9k_enable_regwrite_buffer;
	ah->reg_ops.write_flush = ath9k_regwrite_flush;
	ah->reg_ops.enable_rmw_buffer = ath9k_enable_rmw_buffer;
	ah->reg_ops.rmw_flush = ath9k_reg_rmw_flush;
	ah->reg_ops.rmw = ath9k_reg_rmw;
	priv->ah = ah;

	common = ath9k_hw_common(ah);
	common->ops = &ah->reg_ops;
	common->ps_ops = &ath9k_htc_ps_ops;
	common->bus_ops = &ath9k_usb_bus_ops;
	common->ah = ah;
	common->hw = priv->hw;
	common->priv = priv;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabled = ath9k_htc_btcoex_enable == 1;
	set_bit(ATH_OP_INVALID, &common->op_flags);

	spin_lock_init(&priv->beacon_lock);
	spin_lock_init(&priv->tx.tx_lock);
	mutex_init(&priv->mutex);
	mutex_init(&priv->htc_pm_lock);
	tasklet_init(&priv->rx_tasklet, ath9k_rx_tasklet,
		     (unsigned long)priv);
	tasklet_init(&priv->tx_failed_tasklet, ath9k_tx_failed_tasklet,
		     (unsigned long)priv);
	INIT_DELAYED_WORK(&priv->ani_work, ath9k_htc_ani_work);
	INIT_WORK(&priv->ps_work, ath9k_ps_work);
	INIT_WORK(&priv->fatal_work, ath9k_fatal_work);
	timer_setup(&priv->tx.cleanup_timer, ath9k_htc_tx_cleanup_timer, 0);

	/*
	 * Cache line size is used to size and align various
	 * structures used to communicate with the hardware.
	 */
	ath_read_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	ret = ath9k_hw_init(ah);
	if (ret) {
		ath_err(common,
			"Unable to initialize hardware; initialization status: %d\n",
			ret);
		goto err_hw;
	}

	ret = ath9k_init_queues(priv);
	if (ret)
		goto err_queues;

	for (i = 0; i < ATH9K_HTC_MAX_BCN_VIF; i++)
		priv->beacon.bslot[i] = NULL;
	priv->beacon.slottime = 9;

	ath9k_cmn_init_channels_rates(common);
	ath9k_cmn_init_crypto(ah);
	ath9k_init_misc(priv);
	ath9k_htc_init_btcoex(priv, product);

	return 0;

err_queues:
	ath9k_hw_deinit(ah);
err_hw:

	kfree(ah);
	priv->ah = NULL;

	return ret;
}