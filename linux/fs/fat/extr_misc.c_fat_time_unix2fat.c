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
typedef  int u8 ;
struct tm {int tm_year; int tm_mon; int tm_sec; int tm_hour; int tm_min; int tm_mday; } ;
struct timespec64 {int tv_sec; int tv_nsec; } ;
struct msdos_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  fat_tz_offset (struct msdos_sb_info*) ; 
 int /*<<< orphan*/  time64_to_tm (int,int /*<<< orphan*/ ,struct tm*) ; 

void fat_time_unix2fat(struct msdos_sb_info *sbi, struct timespec64 *ts,
		       __le16 *time, __le16 *date, u8 *time_cs)
{
	struct tm tm;
	time64_to_tm(ts->tv_sec, -fat_tz_offset(sbi), &tm);

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