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
struct pg_tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 char* AppendSeconds (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* EncodeTimezone (char*,int,int) ; 
 int /*<<< orphan*/  MAX_TIME_PRECISION ; 
 char* pg_ltostr_zeropad (char*,int /*<<< orphan*/ ,int) ; 

void
EncodeTimeOnly(struct pg_tm *tm, fsec_t fsec, bool print_tz, int tz, int style, char *str)
{
	str = pg_ltostr_zeropad(str, tm->tm_hour, 2);
	*str++ = ':';
	str = pg_ltostr_zeropad(str, tm->tm_min, 2);
	*str++ = ':';
	str = AppendSeconds(str, tm->tm_sec, fsec, MAX_TIME_PRECISION, true);
	if (print_tz)
		str = EncodeTimezone(str, tz, style);
	*str = '\0';
}