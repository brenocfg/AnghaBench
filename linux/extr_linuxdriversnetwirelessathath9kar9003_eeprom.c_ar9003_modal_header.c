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
struct ar9300_modal_eep_header {int dummy; } ;
struct ar9300_eeprom {struct ar9300_modal_eep_header modalHeader5G; struct ar9300_modal_eep_header modalHeader2G; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;

/* Variables and functions */

__attribute__((used)) static struct ar9300_modal_eep_header *ar9003_modal_header(struct ath_hw *ah,
							   bool is2ghz)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	if (is2ghz)
		return &eep->modalHeader2G;
	else
		return &eep->modalHeader5G;
}