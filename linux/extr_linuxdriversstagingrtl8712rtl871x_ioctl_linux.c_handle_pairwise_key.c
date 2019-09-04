#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  skey; } ;
struct TYPE_8__ {int /*<<< orphan*/  skey; } ;
struct TYPE_7__ {int /*<<< orphan*/  skey; } ;
struct sta_info {TYPE_3__ tkiprxmickey; TYPE_2__ tkiptxmickey; TYPE_1__ x_UncstKey; } ;
struct TYPE_10__ {int key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/  alg; } ;
struct TYPE_11__ {TYPE_4__ crypt; } ;
struct ieee_param {TYPE_5__ u; } ;
struct TYPE_12__ {int busetkipkey; int /*<<< orphan*/  tkip_timer; } ;
struct _adapter {TYPE_6__ securitypriv; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  r8712_setstakey_cmd (struct _adapter*,unsigned char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void handle_pairwise_key(struct sta_info *psta,
				       struct ieee_param *param,
				       struct _adapter *padapter)
{
	/* pairwise key */
	memcpy(psta->x_UncstKey.skey, param->u.crypt.key,
	       (param->u.crypt. key_len > 16 ? 16 : param->u.crypt.key_len));
	if (strcmp(param->u.crypt.alg, "TKIP") == 0) { /* set mic key */
		memcpy(psta->tkiptxmickey. skey,
		       &(param->u.crypt.key[16]), 8);
		memcpy(psta->tkiprxmickey. skey,
		       &(param->u.crypt.key[24]), 8);
		padapter->securitypriv. busetkipkey = false;
		mod_timer(&padapter->securitypriv.tkip_timer,
			  jiffies + msecs_to_jiffies(50));
	}
	r8712_setstakey_cmd(padapter, (unsigned char *)psta, true);
}