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
struct erofs_sb_info {unsigned int max_sync_decompress_pages; } ;

/* Variables and functions */

__attribute__((used)) static bool should_decompress_synchronously(struct erofs_sb_info *sbi,
					    unsigned int nr)
{
	return nr <= sbi->max_sync_decompress_pages;
}