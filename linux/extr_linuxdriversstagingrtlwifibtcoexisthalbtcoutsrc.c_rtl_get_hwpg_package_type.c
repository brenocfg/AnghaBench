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
struct rtl_hal {int /*<<< orphan*/  package_type; } ;

/* Variables and functions */
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 

__attribute__((used)) static u8 rtl_get_hwpg_package_type(struct rtl_priv *rtlpriv)
{
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);

	return rtlhal->package_type;
}