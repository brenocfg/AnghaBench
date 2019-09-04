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
struct rtl_phy {int /*<<< orphan*/  rf_type; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 get_rf_type(struct rtl_phy *rtlphy)
{
	return rtlphy->rf_type;
}