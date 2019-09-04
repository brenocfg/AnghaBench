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
typedef  size_t u16 ;
struct ath_hw {int dummy; } ;
typedef  scalar_t__ int8_t ;
typedef  size_t int16_t ;

/* Variables and functions */
 size_t AR5416_NUM_PDADC_VALUES ; 
 scalar_t__ AR5416_PWR_TABLE_OFFSET_DB ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 

__attribute__((used)) static void ath9k_adjust_pdadc_values(struct ath_hw *ah,
				      int8_t pwr_table_offset,
				      int16_t diff,
				      u8 *pdadcValues)
{
#define NUM_PDADC(diff) (AR5416_NUM_PDADC_VALUES - diff)
	u16 k;

	/* If this is a board that has a pwrTableOffset that differs from
	 * the default AR5416_PWR_TABLE_OFFSET_DB then the start of the
	 * pdadc vs pwr table needs to be adjusted prior to writing to the
	 * chip.
	 */
	if (AR_SREV_9280_20_OR_LATER(ah)) {
		if (AR5416_PWR_TABLE_OFFSET_DB != pwr_table_offset) {
			/* shift the table to start at the new offset */
			for (k = 0; k < (u16)NUM_PDADC(diff); k++ ) {
				pdadcValues[k] = pdadcValues[k + diff];
			}

			/* fill the back of the table */
			for (k = (u16)NUM_PDADC(diff); k < NUM_PDADC(0); k++) {
				pdadcValues[k] = pdadcValues[NUM_PDADC(diff)];
			}
		}
	}
#undef NUM_PDADC
}