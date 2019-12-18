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
 int /*<<< orphan*/  FS_DATA_IO ; 
 int __write_data_page (struct page*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct writeback_control*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_write_data_page(struct page *page,
					struct writeback_control *wbc)
{
	return __write_data_page(page, NULL, NULL, NULL, wbc, FS_DATA_IO);
}