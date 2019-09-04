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
struct btc_coexist {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8812 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool halbtc_is_hw_mailbox_exist(struct btc_coexist *btcoexist)
{
	if (IS_HARDWARE_TYPE_8812(btcoexist->adapter))
		return false;
	else
		return true;
}