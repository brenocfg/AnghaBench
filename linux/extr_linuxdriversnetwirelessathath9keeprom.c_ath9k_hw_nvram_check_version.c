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
struct ath_hw {TYPE_1__* eep_ops; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {int (* get_eeprom_ver ) (struct ath_hw*) ;int (* get_eeprom_rev ) (struct ath_hw*) ;} ;

/* Variables and functions */
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int,int) ; 
 int stub1 (struct ath_hw*) ; 
 int stub2 (struct ath_hw*) ; 
 int stub3 (struct ath_hw*) ; 
 int stub4 (struct ath_hw*) ; 

bool ath9k_hw_nvram_check_version(struct ath_hw *ah, int version, int minrev)
{
	struct ath_common *common = ath9k_hw_common(ah);

	if (ah->eep_ops->get_eeprom_ver(ah) != version ||
	    ah->eep_ops->get_eeprom_rev(ah) < minrev) {
		ath_err(common, "Bad EEPROM VER 0x%04x or REV 0x%04x\n",
			ah->eep_ops->get_eeprom_ver(ah),
			ah->eep_ops->get_eeprom_rev(ah));
		return false;
	}

	return true;
}