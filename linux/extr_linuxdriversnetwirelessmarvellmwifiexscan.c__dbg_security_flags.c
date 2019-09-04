#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  encryption_mode; scalar_t__ wpa2_enabled; scalar_t__ wpa_enabled; scalar_t__ wep_enabled; } ;
struct mwifiex_private {TYPE_4__ sec_info; int /*<<< orphan*/  adapter; } ;
struct mwifiex_bssdescriptor {int /*<<< orphan*/  privacy; TYPE_3__* bcn_rsn_ie; TYPE_5__* bcn_wpa_ie; } ;
struct TYPE_6__ {int /*<<< orphan*/  element_id; } ;
struct TYPE_10__ {TYPE_1__ vend_hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  element_id; } ;
struct TYPE_8__ {TYPE_2__ ieee_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mwifiex_dbg (int /*<<< orphan*/ ,int,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_dbg_security_flags(int log_level, const char *func, const char *desc,
		    struct mwifiex_private *priv,
		    struct mwifiex_bssdescriptor *bss_desc)
{
	_mwifiex_dbg(priv->adapter, log_level,
		     "info: %s: %s:\twpa_ie=%#x wpa2_ie=%#x WEP=%s WPA=%s WPA2=%s\tEncMode=%#x privacy=%#x\n",
		     func, desc,
		     bss_desc->bcn_wpa_ie ?
		     bss_desc->bcn_wpa_ie->vend_hdr.element_id : 0,
		     bss_desc->bcn_rsn_ie ?
		     bss_desc->bcn_rsn_ie->ieee_hdr.element_id : 0,
		     priv->sec_info.wep_enabled ? "e" : "d",
		     priv->sec_info.wpa_enabled ? "e" : "d",
		     priv->sec_info.wpa2_enabled ? "e" : "d",
		     priv->sec_info.encryption_mode,
		     bss_desc->privacy);
}