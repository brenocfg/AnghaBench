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
struct TYPE_4__ {TYPE_1__* indicator; } ;
struct rtl_priv {TYPE_2__ halmac; } ;
struct completion {int dummy; } ;
typedef  enum halmac_feature_id { ____Placeholder_halmac_feature_id } halmac_feature_id ;
struct TYPE_3__ {int /*<<< orphan*/  wait_ms; struct completion* comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_halmac_event (struct rtl_priv*,int) ; 
 int wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_halmac_event(struct rtl_priv *rtlpriv,
			     enum halmac_feature_id id)
{
	struct completion *comp;
	int ret;

	comp = rtlpriv->halmac.indicator[id].comp;
	if (!comp)
		return -1;

	ret = wait_for_completion_timeout(
		comp, rtlpriv->halmac.indicator[id].wait_ms);
	free_halmac_event(rtlpriv, id);
	if (ret > 0)
		return 0;

	return -1;
}