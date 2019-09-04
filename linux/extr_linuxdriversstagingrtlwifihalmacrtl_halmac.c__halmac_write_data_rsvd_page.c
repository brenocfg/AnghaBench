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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ (* halmac_cb_write_data_rsvd_page ) (struct rtl_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct rtl_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _halmac_write_data_rsvd_page(void *p, u8 *buf, u32 size)
{
	struct rtl_priv *rtlpriv = (struct rtl_priv *)p;

	if (rtlpriv->cfg->ops->halmac_cb_write_data_rsvd_page &&
	    rtlpriv->cfg->ops->halmac_cb_write_data_rsvd_page(rtlpriv, buf,
							      size))
		return true;

	return false;
}