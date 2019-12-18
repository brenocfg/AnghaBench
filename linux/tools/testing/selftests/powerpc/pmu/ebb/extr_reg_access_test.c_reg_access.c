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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  ebb_is_supported () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

int reg_access(void)
{
	uint64_t val, expected;

	SKIP_IF(!ebb_is_supported());

	expected = 0x8000000100000000ull;
	mtspr(SPRN_BESCR, expected);
	val = mfspr(SPRN_BESCR);

	FAIL_IF(val != expected);

	expected = 0x0000000001000000ull;
	mtspr(SPRN_EBBHR, expected);
	val = mfspr(SPRN_EBBHR);

	FAIL_IF(val != expected);

	return 0;
}