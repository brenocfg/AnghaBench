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
typedef  int /*<<< orphan*/  timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  EARLY ; 
 int /*<<< orphan*/  LATE ; 
 scalar_t__ TIMESTAMP_IS_NOBEGIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TIMESTAMP_IS_NOEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
EncodeSpecialTimestamp(timestamp dt, char *str)
{
	if (TIMESTAMP_IS_NOBEGIN(dt))
		strcpy(str, EARLY);
	else if (TIMESTAMP_IS_NOEND(dt))
		strcpy(str, LATE);
	else
		abort();				/* shouldn't happen */
}