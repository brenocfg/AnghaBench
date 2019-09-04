#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int typecnt; int charcnt; int leapcnt; int ttisstdcnt; int ttisgmtcnt; } ;
struct TYPE_5__ {TYPE_1__ _bit32; } ;
typedef  TYPE_2__ timelib_tzinfo ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

__attribute__((used)) static void skip_32bit_types(const unsigned char **tzf, timelib_tzinfo *tz)
{
	/* Offset Types */
	*tzf += sizeof(unsigned char) * 6 * tz->_bit32.typecnt;

	/* Abbreviations */
	*tzf += sizeof(char) * tz->_bit32.charcnt;

	/* Leap seconds (only use in 'right/') format */
	if (tz->_bit32.leapcnt) {
		*tzf += sizeof(int32_t) * tz->_bit32.leapcnt * 2;
	}

	/* Standard/Wall Indicators (unused) */
	if (tz->_bit32.ttisstdcnt) {
		*tzf += sizeof(unsigned char) * tz->_bit32.ttisstdcnt;
	}

	/* UT/Local Time Indicators (unused) */
	if (tz->_bit32.ttisgmtcnt) {
		*tzf += sizeof(unsigned char) * tz->_bit32.ttisgmtcnt;
	}
}