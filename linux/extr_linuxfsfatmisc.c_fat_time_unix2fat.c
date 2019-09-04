#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tm {int tm_year; int tm_mon; int tm_sec; int tm_hour; int tm_min; int tm_mday; } ;
struct timespec64 {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int time_offset; scalar_t__ tz_set; } ;
struct msdos_sb_info {TYPE_1__ options; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int tz_minuteswest; } ;

/* Variables and functions */
 int SECS_PER_MIN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 TYPE_2__ sys_tz ; 
 int /*<<< orphan*/  time64_to_tm (int,int,struct tm*) ; 

void fat_time_unix2fat(struct msdos_sb_info *sbi, struct timespec64 *ts,
		       __le16 *time, __le16 *date, u8 *time_cs)
{
	struct tm tm;
	time64_to_tm(ts->tv_sec,
		   (sbi->options.tz_set ? sbi->options.time_offset :
		   -sys_tz.tz_minuteswest) * SECS_PER_MIN, &tm);

	/*  FAT can only support year between 1980 to 2107 */
	if (tm.tm_year < 1980 - 1900) {
		*time = 0;
		*date = cpu_to_le16((0 << 9) | (1 << 5) | 1);
		if (time_cs)
			*time_cs = 0;
		return;
	}
	if (tm.tm_year > 2107 - 1900) {
		*time = cpu_to_le16((23 << 11) | (59 << 5) | 29);
		*date = cpu_to_le16((127 << 9) | (12 << 5) | 31);
		if (time_cs)
			*time_cs = 199;
		return;
	}

	/* from 1900 -> from 1980 */
	tm.tm_year -= 80;
	/* 0~11 -> 1~12 */
	tm.tm_mon++;
	/* 0~59 -> 0~29(2sec counts) */
	tm.tm_sec >>= 1;

	*time = cpu_to_le16(tm.tm_hour << 11 | tm.tm_min << 5 | tm.tm_sec);
	*date = cpu_to_le16(tm.tm_year << 9 | tm.tm_mon << 5 | tm.tm_mday);
	if (time_cs)
		*time_cs = (ts->tv_sec & 1) * 100 + ts->tv_nsec / 10000000;
}