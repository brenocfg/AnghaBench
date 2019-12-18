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
struct page {scalar_t__ mapping; } ;

/* Variables and functions */
 scalar_t__ Z_EROFS_MAPPING_STAGING ; 

__attribute__((used)) static inline bool z_erofs_page_is_staging(struct page *page)
{
	return page->mapping == Z_EROFS_MAPPING_STAGING;
}