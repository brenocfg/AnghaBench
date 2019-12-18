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
struct timespec64 {scalar_t__ tv_sec; unsigned int tv_nsec; } ;
struct super_block {unsigned int s_time_gran; scalar_t__ s_time_min; scalar_t__ s_time_max; } ;
struct inode {struct super_block* i_sb; } ;

/* Variables and functions */
 unsigned int NSEC_PER_SEC ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 scalar_t__ clamp (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

struct timespec64 timestamp_truncate(struct timespec64 t, struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	unsigned int gran = sb->s_time_gran;

	t.tv_sec = clamp(t.tv_sec, sb->s_time_min, sb->s_time_max);
	if (unlikely(t.tv_sec == sb->s_time_max || t.tv_sec == sb->s_time_min))
		t.tv_nsec = 0;

	/* Avoid division in the common cases 1 ns and 1 s. */
	if (gran == 1)
		; /* nothing */
	else if (gran == NSEC_PER_SEC)
		t.tv_nsec = 0;
	else if (gran > 1 && gran < NSEC_PER_SEC)
		t.tv_nsec -= t.tv_nsec % gran;
	else
		WARN(1, "invalid file time granularity: %u", gran);
	return t;
}