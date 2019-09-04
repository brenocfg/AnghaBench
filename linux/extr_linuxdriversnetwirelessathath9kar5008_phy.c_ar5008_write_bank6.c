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
struct ar5416IniArray {int ia_rows; } ;
struct ath_hw {int /*<<< orphan*/ * analogBank6Data; struct ar5416IniArray iniBank6; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_DELAY (unsigned int) ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  INI_RA (struct ar5416IniArray*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar5008_write_bank6(struct ath_hw *ah, unsigned int *writecnt)
{
	struct ar5416IniArray *array = &ah->iniBank6;
	u32 *data = ah->analogBank6Data;
	int r;

	ENABLE_REGWRITE_BUFFER(ah);

	for (r = 0; r < array->ia_rows; r++) {
		REG_WRITE(ah, INI_RA(array, r, 0), data[r]);
		DO_DELAY(*writecnt);
	}

	REGWRITE_BUFFER_FLUSH(ah);
}