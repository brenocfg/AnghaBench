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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {void* charcnt; void* typecnt; void* timecnt; void* leapcnt; void* ttisstdcnt; void* ttisgmtcnt; } ;
struct TYPE_5__ {TYPE_1__ _bit32; } ;
typedef  TYPE_2__ timelib_tzinfo ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,unsigned char const*,int) ; 
 void* timelib_conv_int_unsigned (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_32bit_header(const unsigned char **tzf, timelib_tzinfo *tz)
{
	uint32_t buffer[6];

	memcpy(&buffer, *tzf, sizeof(buffer));
	tz->_bit32.ttisgmtcnt = timelib_conv_int_unsigned(buffer[0]);
	tz->_bit32.ttisstdcnt = timelib_conv_int_unsigned(buffer[1]);
	tz->_bit32.leapcnt    = timelib_conv_int_unsigned(buffer[2]);
	tz->_bit32.timecnt    = timelib_conv_int_unsigned(buffer[3]);
	tz->_bit32.typecnt    = timelib_conv_int_unsigned(buffer[4]);
	tz->_bit32.charcnt    = timelib_conv_int_unsigned(buffer[5]);

	*tzf += sizeof(buffer);
}