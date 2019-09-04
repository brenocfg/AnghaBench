#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  eepMisc; } ;
struct TYPE_5__ {TYPE_1__ baseEepHeader; } ;
struct TYPE_6__ {TYPE_2__ map9287; } ;
struct ath_hw {TYPE_3__ eeprom; } ;

/* Variables and functions */

__attribute__((used)) static u8 ath9k_hw_ar9287_get_eepmisc(struct ath_hw *ah)
{
	return ah->eeprom.map9287.baseEepHeader.eepMisc;
}