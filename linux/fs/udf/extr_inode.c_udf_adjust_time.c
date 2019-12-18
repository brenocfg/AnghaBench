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
struct timespec64 {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct udf_inode_info {struct timespec64 i_crtime; } ;

/* Variables and functions */

__attribute__((used)) static void udf_adjust_time(struct udf_inode_info *iinfo, struct timespec64 time)
{
	if (iinfo->i_crtime.tv_sec > time.tv_sec ||
	    (iinfo->i_crtime.tv_sec == time.tv_sec &&
	     iinfo->i_crtime.tv_nsec > time.tv_nsec))
		iinfo->i_crtime = time;
}