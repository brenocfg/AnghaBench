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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  PGDUMP_STRFTIME_FMT ; 
 int /*<<< orphan*/  ahprintf (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ strftime (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dumpTimestamp(ArchiveHandle *AH, const char *msg, time_t tim)
{
	char		buf[64];

	if (strftime(buf, sizeof(buf), PGDUMP_STRFTIME_FMT, localtime(&tim)) != 0)
		ahprintf(AH, "-- %s %s\n\n", msg, buf);
}