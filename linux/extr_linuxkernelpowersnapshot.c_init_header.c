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
struct swsusp_info {int /*<<< orphan*/  size; int /*<<< orphan*/  pages; int /*<<< orphan*/  image_pages; int /*<<< orphan*/  num_physpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  get_num_physpages () ; 
 int init_header_complete (struct swsusp_info*) ; 
 int /*<<< orphan*/  memset (struct swsusp_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nr_copy_pages ; 
 int /*<<< orphan*/  snapshot_get_image_size () ; 

__attribute__((used)) static int init_header(struct swsusp_info *info)
{
	memset(info, 0, sizeof(struct swsusp_info));
	info->num_physpages = get_num_physpages();
	info->image_pages = nr_copy_pages;
	info->pages = snapshot_get_image_size();
	info->size = info->pages;
	info->size <<= PAGE_SHIFT;
	return init_header_complete(info);
}