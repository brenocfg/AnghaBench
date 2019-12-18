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
struct lib80211_crypt_info {struct lib80211_crypt_data** crypt; int /*<<< orphan*/  crypt_deinit_timer; } ;
struct lib80211_crypt_data {TYPE_1__* ops; int /*<<< orphan*/  priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int NUM_WEP_KEYS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct lib80211_crypt_data*) ; 
 int /*<<< orphan*/  lib80211_crypt_deinit_entries (struct lib80211_crypt_info*,int) ; 
 int /*<<< orphan*/  lib80211_crypt_quiescing (struct lib80211_crypt_info*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void lib80211_crypt_info_free(struct lib80211_crypt_info *info)
{
	int i;

        lib80211_crypt_quiescing(info);
        del_timer_sync(&info->crypt_deinit_timer);
        lib80211_crypt_deinit_entries(info, 1);

        for (i = 0; i < NUM_WEP_KEYS; i++) {
                struct lib80211_crypt_data *crypt = info->crypt[i];
                if (crypt) {
                        if (crypt->ops) {
                                crypt->ops->deinit(crypt->priv);
                                module_put(crypt->ops->owner);
                        }
                        kfree(crypt);
                        info->crypt[i] = NULL;
                }
        }
}