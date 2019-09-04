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
struct il_priv {int is_open; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_READY ; 
 int /*<<< orphan*/  UCODE_READY_TIMEOUT ; 
 int __il4965_up (struct il_priv*) ; 
 int /*<<< orphan*/  il4965_led_enable (struct il_priv*) ; 
 scalar_t__ il_is_rfkill (struct il_priv*) ; 
 int /*<<< orphan*/  jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
il4965_mac_start(struct ieee80211_hw *hw)
{
	struct il_priv *il = hw->priv;
	int ret;

	D_MAC80211("enter\n");

	/* we should be verifying the device is ready to be opened */
	mutex_lock(&il->mutex);
	ret = __il4965_up(il);
	mutex_unlock(&il->mutex);

	if (ret)
		return ret;

	if (il_is_rfkill(il))
		goto out;

	D_INFO("Start UP work done.\n");

	/* Wait for START_ALIVE from Run Time ucode. Otherwise callbacks from
	 * mac80211 will not be run successfully. */
	ret = wait_event_timeout(il->wait_command_queue,
				 test_bit(S_READY, &il->status),
				 UCODE_READY_TIMEOUT);
	if (!ret) {
		if (!test_bit(S_READY, &il->status)) {
			IL_ERR("START_ALIVE timeout after %dms.\n",
				jiffies_to_msecs(UCODE_READY_TIMEOUT));
			return -ETIMEDOUT;
		}
	}

	il4965_led_enable(il);

out:
	il->is_open = 1;
	D_MAC80211("leave\n");
	return 0;
}