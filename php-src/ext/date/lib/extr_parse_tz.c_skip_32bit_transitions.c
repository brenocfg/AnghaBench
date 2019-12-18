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
struct TYPE_4__ {int timecnt; } ;
struct TYPE_5__ {TYPE_1__ _bit32; } ;
typedef  TYPE_2__ timelib_tzinfo ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

__attribute__((used)) static void skip_32bit_transitions(const unsigned char **tzf, timelib_tzinfo *tz)
{
	if (tz->_bit32.timecnt) {
		*tzf += (sizeof(int32_t) * tz->_bit32.timecnt);
		*tzf += sizeof(unsigned char) * tz->_bit32.timecnt;
	}
}