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
struct TYPE_4__ {scalar_t__ enable_paprd; } ;
struct TYPE_3__ {int hw_caps; } ;
struct ath_hw {TYPE_2__ config; TYPE_1__ caps; } ;

/* Variables and functions */
 int ATH9K_HW_CAP_PAPRD ; 

bool ar9003_is_paprd_enabled(struct ath_hw *ah)
{
	if ((ah->caps.hw_caps & ATH9K_HW_CAP_PAPRD) && ah->config.enable_paprd)
		return true;

	return false;
}