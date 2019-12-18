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
typedef  int uint8_t ;
typedef  int u16 ;
struct timestamp {int centiseconds; int hundredsOfMicroseconds; int microseconds; int /*<<< orphan*/  second; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; int /*<<< orphan*/  year; int /*<<< orphan*/  typeAndTimezone; } ;
struct timespec64 {int tv_sec; int tv_nsec; } ;
typedef  int int16_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mktime64 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
udf_disk_stamp_to_time(struct timespec64 *dest, struct timestamp src)
{
	u16 typeAndTimezone = le16_to_cpu(src.typeAndTimezone);
	u16 year = le16_to_cpu(src.year);
	uint8_t type = typeAndTimezone >> 12;
	int16_t offset;

	if (type == 1) {
		offset = typeAndTimezone << 4;
		/* sign extent offset */
		offset = (offset >> 4);
		if (offset == -2047) /* unspecified offset */
			offset = 0;
	} else
		offset = 0;

	dest->tv_sec = mktime64(year, src.month, src.day, src.hour, src.minute,
			src.second);
	dest->tv_sec -= offset * 60;
	dest->tv_nsec = 1000 * (src.centiseconds * 10000 +
			src.hundredsOfMicroseconds * 100 + src.microseconds);
	/*
	 * Sanitize nanosecond field since reportedly some filesystems are
	 * recorded with bogus sub-second values.
	 */
	dest->tv_nsec %= NSEC_PER_SEC;
}