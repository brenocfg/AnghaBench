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
typedef  int /*<<< orphan*/  RangeType ;

/* Variables and functions */
 char RANGE_CONTAIN_EMPTY ; 
 int VARSIZE (int /*<<< orphan*/ *) ; 

void
range_set_contain_empty(RangeType *range)
{
	char	   *flagsp;

	/* flag byte is datum's last byte */
	flagsp = (char *) range + VARSIZE(range) - 1;

	*flagsp |= RANGE_CONTAIN_EMPTY;
}