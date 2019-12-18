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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  __has_merged_page (struct bio*,int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __submit_bio (struct f2fs_sb_info*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f2fs_submit_ipu_bio(struct f2fs_sb_info *sbi, struct bio **bio,
							struct page *page)
{
	if (!bio)
		return;

	if (!__has_merged_page(*bio, NULL, page, 0))
		return;

	__submit_bio(sbi, *bio, DATA);
	*bio = NULL;
}