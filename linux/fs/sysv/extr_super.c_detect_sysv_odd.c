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
struct sysv_sb_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int detect_sysv (struct sysv_sb_info*,struct buffer_head*) ; 

__attribute__((used)) static int detect_sysv_odd(struct sysv_sb_info *sbi, struct buffer_head *bh)
{
	int size = detect_sysv(sbi, bh);

	return size>2 ? 0 : size;
}