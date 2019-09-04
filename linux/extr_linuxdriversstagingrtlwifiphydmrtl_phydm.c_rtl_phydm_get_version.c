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
typedef  int /*<<< orphan*/  u32 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (struct rtl_priv*) ; 
 int /*<<< orphan*/  RELEASE_VERSION_8822B ; 

__attribute__((used)) static u32 rtl_phydm_get_version(struct rtl_priv *rtlpriv)
{
	u32 ver = 0;

	if (IS_HARDWARE_TYPE_8822B(rtlpriv))
		ver = RELEASE_VERSION_8822B;

	return ver;
}