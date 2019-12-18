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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_META_IO ; 
 int __f2fs_write_meta_page (struct page*,struct writeback_control*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_write_meta_page(struct page *page,
				struct writeback_control *wbc)
{
	return __f2fs_write_meta_page(page, wbc, FS_META_IO);
}