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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
ar8xxx_byte_to_str(char *buf, int len, u64 byte)
{
	unsigned long b;
	const char *unit;

	if (byte >= 0x40000000) { /* 1 GiB */
		b = byte * 10 / 0x40000000;
		unit = "GiB";
	} else if (byte >= 0x100000) { /* 1 MiB */
		b = byte * 10 / 0x100000;
		unit = "MiB";
	} else if (byte >= 0x400) { /* 1 KiB */
		b = byte * 10 / 0x400;
		unit = "KiB";
	} else {
		b = byte;
		unit = "Byte";
	}
	if (strcmp(unit, "Byte"))
		snprintf(buf, len, "%lu.%lu %s", b / 10, b % 10, unit);
	else
		snprintf(buf, len, "%lu %s", b, unit);
}