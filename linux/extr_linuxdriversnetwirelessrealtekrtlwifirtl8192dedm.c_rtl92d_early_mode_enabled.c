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
struct TYPE_2__ {scalar_t__ link_state; scalar_t__ vendor; } ;
struct dig_t {int last_min_undec_pwdb_for_dm; int min_undec_pwdb_for_dm; } ;
struct rtl_priv {TYPE_1__ mac80211; struct dig_t dm_digtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ PEER_CISCO ; 
 int /*<<< orphan*/  REG_EARLY_MODE_CONTROL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl92d_early_mode_enabled(struct rtl_priv *rtlpriv)
{
	struct dig_t *de_digtable = &rtlpriv->dm_digtable;

	if ((rtlpriv->mac80211.link_state >= MAC80211_LINKED) &&
	    (rtlpriv->mac80211.vendor == PEER_CISCO)) {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "IOT_PEER = CISCO\n");
		if (de_digtable->last_min_undec_pwdb_for_dm >= 50
		    && de_digtable->min_undec_pwdb_for_dm < 50) {
			rtl_write_byte(rtlpriv, REG_EARLY_MODE_CONTROL, 0x00);
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "Early Mode Off\n");
		} else if (de_digtable->last_min_undec_pwdb_for_dm <= 55 &&
			   de_digtable->min_undec_pwdb_for_dm > 55) {
			rtl_write_byte(rtlpriv, REG_EARLY_MODE_CONTROL, 0x0f);
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "Early Mode On\n");
		}
	} else if (!(rtl_read_byte(rtlpriv, REG_EARLY_MODE_CONTROL) & 0xf)) {
		rtl_write_byte(rtlpriv, REG_EARLY_MODE_CONTROL, 0x0f);
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "Early Mode On\n");
	}
}