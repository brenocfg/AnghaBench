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
typedef  int /*<<< orphan*/  DateADT ;

/* Variables and functions */
 scalar_t__ DATE_IS_NOBEGIN (int /*<<< orphan*/ ) ; 
 scalar_t__ DATE_IS_NOEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EARLY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LATE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

void
EncodeSpecialDate(DateADT dt, char *str)
{
	if (DATE_IS_NOBEGIN(dt))
		strcpy(str, EARLY);
	else if (DATE_IS_NOEND(dt))
		strcpy(str, LATE);
	else						/* shouldn't happen */
		elog(ERROR, "invalid argument for EncodeSpecialDate");
}