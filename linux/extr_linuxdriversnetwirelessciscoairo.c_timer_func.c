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
struct net_device {struct airo_info* ml_priv; } ;
struct TYPE_2__ {int authType; } ;
struct airo_info {int /*<<< orphan*/  expires; int /*<<< orphan*/  jobs; int /*<<< orphan*/  sem; int /*<<< orphan*/  flags; TYPE_1__ config; int /*<<< orphan*/  defindex; int /*<<< orphan*/  keyindex; } ;

/* Variables and functions */
#define  AUTH_ENCRYPT 129 
 int AUTH_OPEN ; 
#define  AUTH_SHAREDKEY 128 
 int /*<<< orphan*/  FLAG_COMMIT ; 
 int HZ ; 
 int /*<<< orphan*/  JOB_AUTOWEP ; 
 int /*<<< orphan*/  RUN_AT (int) ; 
 int /*<<< orphan*/  auto_wep ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readConfigRid (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_wep_tx_idx (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeConfigRid (struct airo_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_func( struct net_device *dev ) {
	struct airo_info *apriv = dev->ml_priv;

/* We don't have a link so try changing the authtype */
	readConfigRid(apriv, 0);
	disable_MAC(apriv, 0);
	switch(apriv->config.authType) {
		case AUTH_ENCRYPT:
/* So drop to OPEN */
			apriv->config.authType = AUTH_OPEN;
			break;
		case AUTH_SHAREDKEY:
			if (apriv->keyindex < auto_wep) {
				set_wep_tx_idx(apriv, apriv->keyindex, 0, 0);
				apriv->config.authType = AUTH_SHAREDKEY;
				apriv->keyindex++;
			} else {
			        /* Drop to ENCRYPT */
				apriv->keyindex = 0;
				set_wep_tx_idx(apriv, apriv->defindex, 0, 0);
				apriv->config.authType = AUTH_ENCRYPT;
			}
			break;
		default:  /* We'll escalate to SHAREDKEY */
			apriv->config.authType = AUTH_SHAREDKEY;
	}
	set_bit (FLAG_COMMIT, &apriv->flags);
	writeConfigRid(apriv, 0);
	enable_MAC(apriv, 0);
	up(&apriv->sem);

/* Schedule check to see if the change worked */
	clear_bit(JOB_AUTOWEP, &apriv->jobs);
	apriv->expires = RUN_AT(HZ*3);
}