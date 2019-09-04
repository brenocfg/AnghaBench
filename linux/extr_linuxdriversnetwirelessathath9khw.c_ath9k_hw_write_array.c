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
struct ath_hw {int dummy; } ;
struct ar5416IniArray {int ia_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_DELAY (unsigned int) ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  INI_RA (struct ar5416IniArray const*,int,int) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ath9k_hw_write_array(struct ath_hw *ah, const struct ar5416IniArray *array,
			  int column, unsigned int *writecnt)
{
	int r;

	ENABLE_REGWRITE_BUFFER(ah);
	for (r = 0; r < array->ia_rows; r++) {
		REG_WRITE(ah, INI_RA(array, r, 0),
			  INI_RA(array, r, column));
		DO_DELAY(*writecnt);
	}
	REGWRITE_BUFFER_FLUSH(ah);
}