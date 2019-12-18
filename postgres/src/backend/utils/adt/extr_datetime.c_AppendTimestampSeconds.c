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
struct pg_tm {int /*<<< orphan*/  tm_sec; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 char* AppendSeconds (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX_TIMESTAMP_PRECISION ; 

__attribute__((used)) static char *
AppendTimestampSeconds(char *cp, struct pg_tm *tm, fsec_t fsec)
{
	return AppendSeconds(cp, tm->tm_sec, fsec, MAX_TIMESTAMP_PRECISION, true);
}