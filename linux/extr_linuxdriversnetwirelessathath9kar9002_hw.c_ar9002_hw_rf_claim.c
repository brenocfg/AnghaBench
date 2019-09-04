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
typedef  int u32 ;
struct TYPE_2__ {int analog5GhzRev; } ;
struct ath_hw {TYPE_1__ hw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY (int /*<<< orphan*/ ) ; 
#define  AR_RAD2122_SREV_MAJOR 131 
#define  AR_RAD2133_SREV_MAJOR 130 
#define  AR_RAD5122_SREV_MAJOR 129 
#define  AR_RAD5133_SREV_MAJOR 128 
 int AR_RADIO_SREV_MAJOR ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int ar9002_hw_get_radiorev (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*,int) ; 

int ar9002_hw_rf_claim(struct ath_hw *ah)
{
	u32 val;

	REG_WRITE(ah, AR_PHY(0), 0x00000007);

	val = ar9002_hw_get_radiorev(ah);
	switch (val & AR_RADIO_SREV_MAJOR) {
	case 0:
		val = AR_RAD5133_SREV_MAJOR;
		break;
	case AR_RAD5133_SREV_MAJOR:
	case AR_RAD5122_SREV_MAJOR:
	case AR_RAD2133_SREV_MAJOR:
	case AR_RAD2122_SREV_MAJOR:
		break;
	default:
		ath_err(ath9k_hw_common(ah),
			"Radio Chip Rev 0x%02X not supported\n",
			val & AR_RADIO_SREV_MAJOR);
		return -EOPNOTSUPP;
	}

	ah->hw_version.analog5GhzRev = val;

	return 0;
}