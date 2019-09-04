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
struct TYPE_2__ {int /*<<< orphan*/ * internal; } ;
struct rtl_priv {TYPE_1__ halmac; } ;
struct halmac_adapter {int dummy; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_SUCCESS ; 
 int /*<<< orphan*/  deinit_priv (TYPE_1__*) ; 
 int halmac_deinit_adapter (struct halmac_adapter*) ; 
 int /*<<< orphan*/  halmac_halt_api (struct halmac_adapter*) ; 
 struct halmac_adapter* rtlpriv_to_halmac (struct rtl_priv*) ; 

int rtl_halmac_deinit_adapter(struct rtl_priv *rtlpriv)
{
	struct halmac_adapter *halmac;
	enum halmac_ret_status status;
	int err = 0;

	halmac = rtlpriv_to_halmac(rtlpriv);
	if (!halmac) {
		err = 0;
		goto out;
	}

	deinit_priv(&rtlpriv->halmac);

	halmac_halt_api(halmac);

	status = halmac_deinit_adapter(halmac);
	rtlpriv->halmac.internal = NULL;
	if (status != HALMAC_RET_SUCCESS) {
		err = -1;
		goto out;
	}

out:
	return err;
}