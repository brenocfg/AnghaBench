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
struct writeback_control {scalar_t__ sync_mode; long nr_to_write; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 long BIO_MAX_PAGES ; 
 int NODE ; 
 scalar_t__ WB_SYNC_NONE ; 

__attribute__((used)) static inline long nr_pages_to_write(struct f2fs_sb_info *sbi, int type,
					struct writeback_control *wbc)
{
	long nr_to_write, desired;

	if (wbc->sync_mode != WB_SYNC_NONE)
		return 0;

	nr_to_write = wbc->nr_to_write;
	desired = BIO_MAX_PAGES;
	if (type == NODE)
		desired <<= 1;

	wbc->nr_to_write = desired;
	return desired - nr_to_write;
}