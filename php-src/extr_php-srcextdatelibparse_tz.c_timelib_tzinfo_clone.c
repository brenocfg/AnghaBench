#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char ttinfo ;
typedef  char tlinfo ;
struct TYPE_8__ {int leapcnt; int timecnt; int typecnt; int charcnt; int /*<<< orphan*/  ttisstdcnt; int /*<<< orphan*/  ttisgmtcnt; } ;
struct TYPE_7__ {int /*<<< orphan*/  charcnt; int /*<<< orphan*/  typecnt; int /*<<< orphan*/  timecnt; int /*<<< orphan*/  leapcnt; int /*<<< orphan*/  ttisstdcnt; int /*<<< orphan*/  ttisgmtcnt; } ;
struct TYPE_9__ {char* trans; unsigned char* trans_idx; char* type; char* timezone_abbr; char* leap_times; TYPE_2__ bit64; TYPE_1__ _bit32; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ timelib_tzinfo ;
typedef  char int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ timelib_malloc (int) ; 
 TYPE_3__* timelib_tzinfo_ctor (int /*<<< orphan*/ ) ; 

timelib_tzinfo *timelib_tzinfo_clone(timelib_tzinfo *tz)
{
	timelib_tzinfo *tmp = timelib_tzinfo_ctor(tz->name);
	tmp->_bit32.ttisgmtcnt = tz->_bit32.ttisgmtcnt;
	tmp->_bit32.ttisstdcnt = tz->_bit32.ttisstdcnt;
	tmp->_bit32.leapcnt = tz->_bit32.leapcnt;
	tmp->_bit32.timecnt = tz->_bit32.timecnt;
	tmp->_bit32.typecnt = tz->_bit32.typecnt;
	tmp->_bit32.charcnt = tz->_bit32.charcnt;
	tmp->bit64.ttisgmtcnt = tz->bit64.ttisgmtcnt;
	tmp->bit64.ttisstdcnt = tz->bit64.ttisstdcnt;
	tmp->bit64.leapcnt = tz->bit64.leapcnt;
	tmp->bit64.timecnt = tz->bit64.timecnt;
	tmp->bit64.typecnt = tz->bit64.typecnt;
	tmp->bit64.charcnt = tz->bit64.charcnt;

	if (tz->bit64.timecnt) {
		tmp->trans = (int64_t *) timelib_malloc(tz->bit64.timecnt * sizeof(int64_t));
		tmp->trans_idx = (unsigned char*) timelib_malloc(tz->bit64.timecnt * sizeof(unsigned char));
		memcpy(tmp->trans, tz->trans, tz->bit64.timecnt * sizeof(int64_t));
		memcpy(tmp->trans_idx, tz->trans_idx, tz->bit64.timecnt * sizeof(unsigned char));
	}

	tmp->type = (ttinfo*) timelib_malloc(tz->bit64.typecnt * sizeof(ttinfo));
	memcpy(tmp->type, tz->type, tz->bit64.typecnt * sizeof(ttinfo));

	tmp->timezone_abbr = (char*) timelib_malloc(tz->bit64.charcnt);
	memcpy(tmp->timezone_abbr, tz->timezone_abbr, tz->bit64.charcnt);

	if (tz->bit64.leapcnt) {
		tmp->leap_times = (tlinfo*) timelib_malloc(tz->bit64.leapcnt * sizeof(tlinfo));
		memcpy(tmp->leap_times, tz->leap_times, tz->bit64.leapcnt * sizeof(tlinfo));
	}

	return tmp;
}