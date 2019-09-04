#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERFON ; 
 int /*<<< orphan*/  exhalbtc_ips_notify (struct btc_coexist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exhalbtc_scan_notify (struct btc_coexist*,int) ; 
 struct btc_coexist* rtl_btc_coexist (struct rtl_priv*) ; 

void rtl_btc_ips_notify(struct rtl_priv *rtlpriv, u8 type)
{
	struct btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	if (!btcoexist)
		return;

	exhalbtc_ips_notify(btcoexist, type);

	if (type == ERFON) {
		/* In some situation, it doesn't scan after leaving IPS, and
		 * this will cause btcoex in wrong state.
		 */
		exhalbtc_scan_notify(btcoexist, 1);
		exhalbtc_scan_notify(btcoexist, 0);
	}
}