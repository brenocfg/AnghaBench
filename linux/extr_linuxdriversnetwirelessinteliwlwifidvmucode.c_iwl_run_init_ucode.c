#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct iwl_priv {int ucode_loaded; int /*<<< orphan*/  trans; int /*<<< orphan*/  notif_wait; TYPE_2__* fw; int /*<<< orphan*/  mutex; } ;
struct iwl_notification_wait {int dummy; } ;
struct TYPE_4__ {TYPE_1__* img; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  CALIBRATION_COMPLETE_NOTIFICATION 129 
#define  CALIBRATION_RES_NOTIFICATION 128 
 size_t IWL_UCODE_INIT ; 
 int /*<<< orphan*/  UCODE_CALIB_TIMEOUT ; 
 int iwl_init_alive_start (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_priv*) ; 
 int iwl_load_ucode_wait_alive (struct iwl_priv*,size_t) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwlagn_wait_calib ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_run_init_ucode(struct iwl_priv *priv)
{
	struct iwl_notification_wait calib_wait;
	static const u16 calib_complete[] = {
		CALIBRATION_RES_NOTIFICATION,
		CALIBRATION_COMPLETE_NOTIFICATION
	};
	int ret;

	lockdep_assert_held(&priv->mutex);

	/* No init ucode required? Curious, but maybe ok */
	if (!priv->fw->img[IWL_UCODE_INIT].num_sec)
		return 0;

	iwl_init_notification_wait(&priv->notif_wait, &calib_wait,
				   calib_complete, ARRAY_SIZE(calib_complete),
				   iwlagn_wait_calib, priv);

	/* Will also start the device */
	ret = iwl_load_ucode_wait_alive(priv, IWL_UCODE_INIT);
	if (ret)
		goto error;

	ret = iwl_init_alive_start(priv);
	if (ret)
		goto error;

	/*
	 * Some things may run in the background now, but we
	 * just wait for the calibration complete notification.
	 */
	ret = iwl_wait_notification(&priv->notif_wait, &calib_wait,
					UCODE_CALIB_TIMEOUT);

	goto out;

 error:
	iwl_remove_notification(&priv->notif_wait, &calib_wait);
 out:
	/* Whatever happened, stop the device */
	iwl_trans_stop_device(priv->trans);
	priv->ucode_loaded = false;

	return ret;
}