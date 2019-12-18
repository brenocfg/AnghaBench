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
struct page {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_sit_addr (struct f2fs_sb_info*,unsigned int) ; 
 struct page* f2fs_get_meta_page_nofail (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *get_current_sit_page(struct f2fs_sb_info *sbi,
					unsigned int segno)
{
	return f2fs_get_meta_page_nofail(sbi, current_sit_addr(sbi, segno));
}