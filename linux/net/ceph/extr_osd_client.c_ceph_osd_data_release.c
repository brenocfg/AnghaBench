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
struct ceph_osd_data {scalar_t__ type; int /*<<< orphan*/  pagelist; int /*<<< orphan*/  pages; scalar_t__ length; scalar_t__ alignment; scalar_t__ own_pages; } ;

/* Variables and functions */
 scalar_t__ CEPH_OSD_DATA_TYPE_PAGELIST ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_PAGES ; 
 int calc_pages_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osd_data_init (struct ceph_osd_data*) ; 
 int /*<<< orphan*/  ceph_pagelist_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_release_page_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ceph_osd_data_release(struct ceph_osd_data *osd_data)
{
	if (osd_data->type == CEPH_OSD_DATA_TYPE_PAGES && osd_data->own_pages) {
		int num_pages;

		num_pages = calc_pages_for((u64)osd_data->alignment,
						(u64)osd_data->length);
		ceph_release_page_vector(osd_data->pages, num_pages);
	} else if (osd_data->type == CEPH_OSD_DATA_TYPE_PAGELIST) {
		ceph_pagelist_release(osd_data->pagelist);
	}
	ceph_osd_data_init(osd_data);
}