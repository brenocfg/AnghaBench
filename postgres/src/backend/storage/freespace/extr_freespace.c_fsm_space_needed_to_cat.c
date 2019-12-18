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
typedef  int uint8 ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FSM_CAT_STEP ; 
 scalar_t__ MaxFSMRequestSize ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static uint8
fsm_space_needed_to_cat(Size needed)
{
	int			cat;

	/* Can't ask for more space than the highest category represents */
	if (needed > MaxFSMRequestSize)
		elog(ERROR, "invalid FSM request size %zu", needed);

	if (needed == 0)
		return 1;

	cat = (needed + FSM_CAT_STEP - 1) / FSM_CAT_STEP;

	if (cat > 255)
		cat = 255;

	return (uint8) cat;
}