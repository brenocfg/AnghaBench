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
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int ECPG_INFORMIX_NUM_OVERFLOW ; 
 int ECPG_INFORMIX_NUM_UNDERFLOW ; 
 scalar_t__ PGTYPES_NUM_OVERFLOW ; 
 scalar_t__ PGTYPES_NUM_UNDERFLOW ; 
 int /*<<< orphan*/  PGTYPESnumeric_add ; 
 int /*<<< orphan*/  deccall3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 

int
decadd(decimal *arg1, decimal *arg2, decimal *sum)
{
	errno = 0;
	deccall3(arg1, arg2, sum, PGTYPESnumeric_add);

	if (errno == PGTYPES_NUM_OVERFLOW)
		return ECPG_INFORMIX_NUM_OVERFLOW;
	else if (errno == PGTYPES_NUM_UNDERFLOW)
		return ECPG_INFORMIX_NUM_UNDERFLOW;
	else if (errno != 0)
		return -1;
	else
		return 0;
}