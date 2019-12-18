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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct ceph_osd_data {int pages_from_pool; int own_pages; int /*<<< orphan*/  alignment; int /*<<< orphan*/  length; struct page** pages; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_DATA_TYPE_PAGES ; 

__attribute__((used)) static void ceph_osd_data_pages_init(struct ceph_osd_data *osd_data,
			struct page **pages, u64 length, u32 alignment,
			bool pages_from_pool, bool own_pages)
{
	osd_data->type = CEPH_OSD_DATA_TYPE_PAGES;
	osd_data->pages = pages;
	osd_data->length = length;
	osd_data->alignment = alignment;
	osd_data->pages_from_pool = pages_from_pool;
	osd_data->own_pages = own_pages;
}