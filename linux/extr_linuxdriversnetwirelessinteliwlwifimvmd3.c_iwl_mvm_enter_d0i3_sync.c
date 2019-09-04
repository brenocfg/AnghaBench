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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_notification_wait {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  notif_wait; TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  D3_CONFIG_CMD 128 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_init_notification_wait (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iwl_mvm_enter_d0i3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_remove_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*) ; 
 int iwl_wait_notification (int /*<<< orphan*/ *,struct iwl_notification_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_enter_d0i3_sync(struct iwl_mvm *mvm)
{
	struct iwl_notification_wait wait_d3;
	static const u16 d3_notif[] = { D3_CONFIG_CMD };
	int ret;

	iwl_init_notification_wait(&mvm->notif_wait, &wait_d3,
				   d3_notif, ARRAY_SIZE(d3_notif),
				   NULL, NULL);

	ret = iwl_mvm_enter_d0i3(mvm->hw->priv);
	if (ret)
		goto remove_notif;

	ret = iwl_wait_notification(&mvm->notif_wait, &wait_d3, HZ);
	WARN_ON_ONCE(ret);
	return ret;

remove_notif:
	iwl_remove_notification(&mvm->notif_wait, &wait_d3);
	return ret;
}