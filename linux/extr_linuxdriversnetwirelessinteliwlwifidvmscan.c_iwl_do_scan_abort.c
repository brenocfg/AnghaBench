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
struct iwl_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*,...) ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 
 int /*<<< orphan*/  STATUS_SCAN_ABORTING ; 
 int /*<<< orphan*/  iwl_force_scan_end (struct iwl_priv*) ; 
 int iwl_send_scan_abort (struct iwl_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_do_scan_abort(struct iwl_priv *priv)
{
	int ret;

	lockdep_assert_held(&priv->mutex);

	if (!test_bit(STATUS_SCANNING, &priv->status)) {
		IWL_DEBUG_SCAN(priv, "Not performing scan to abort\n");
		return;
	}

	if (test_and_set_bit(STATUS_SCAN_ABORTING, &priv->status)) {
		IWL_DEBUG_SCAN(priv, "Scan abort in progress\n");
		return;
	}

	ret = iwl_send_scan_abort(priv);
	if (ret) {
		IWL_DEBUG_SCAN(priv, "Send scan abort failed %d\n", ret);
		iwl_force_scan_end(priv);
	} else
		IWL_DEBUG_SCAN(priv, "Successfully send scan abort\n");
}