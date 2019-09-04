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
struct mib_local {int /*<<< orphan*/  preamble_type; int /*<<< orphan*/  promiscuous_mode; int /*<<< orphan*/  ssid_size; int /*<<< orphan*/  txautorate_fallback; int /*<<< orphan*/  beacon_enable; } ;
struct at76_priv {TYPE_1__* hw; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MIB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIB_LOCAL ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int at76_get_mib (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mib_local*,int) ; 
 int /*<<< orphan*/  kfree (struct mib_local*) ; 
 struct mib_local* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at76_dump_mib_local(struct at76_priv *priv)
{
	int ret;
	struct mib_local *m = kmalloc(sizeof(*m), GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_LOCAL, m, sizeof(*m));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (LOCAL) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB LOCAL: beacon_enable %d "
		 "txautorate_fallback %d ssid_size %d promiscuous_mode %d "
		 "preamble_type %d", wiphy_name(priv->hw->wiphy),
		 m->beacon_enable,
		 m->txautorate_fallback, m->ssid_size, m->promiscuous_mode,
		 m->preamble_type);
exit:
	kfree(m);
}