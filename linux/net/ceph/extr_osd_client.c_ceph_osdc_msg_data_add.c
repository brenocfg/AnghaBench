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
typedef  scalar_t__ u64 ;
struct ceph_osd_data {scalar_t__ type; int /*<<< orphan*/  bvec_pos; int /*<<< orphan*/  bio_pos; int /*<<< orphan*/  pagelist; int /*<<< orphan*/  alignment; int /*<<< orphan*/  pages; } ;
struct ceph_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_BIO ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_BVECS ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_NONE ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_PAGELIST ; 
 scalar_t__ CEPH_OSD_DATA_TYPE_PAGES ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  ceph_msg_data_add_bio (struct ceph_msg*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ceph_msg_data_add_bvecs (struct ceph_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_msg_data_add_pagelist (struct ceph_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg_data_add_pages (struct ceph_msg*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_osd_data_length (struct ceph_osd_data*) ; 

__attribute__((used)) static void ceph_osdc_msg_data_add(struct ceph_msg *msg,
				struct ceph_osd_data *osd_data)
{
	u64 length = ceph_osd_data_length(osd_data);

	if (osd_data->type == CEPH_OSD_DATA_TYPE_PAGES) {
		BUG_ON(length > (u64) SIZE_MAX);
		if (length)
			ceph_msg_data_add_pages(msg, osd_data->pages,
					length, osd_data->alignment);
	} else if (osd_data->type == CEPH_OSD_DATA_TYPE_PAGELIST) {
		BUG_ON(!length);
		ceph_msg_data_add_pagelist(msg, osd_data->pagelist);
#ifdef CONFIG_BLOCK
	} else if (osd_data->type == CEPH_OSD_DATA_TYPE_BIO) {
		ceph_msg_data_add_bio(msg, &osd_data->bio_pos, length);
#endif
	} else if (osd_data->type == CEPH_OSD_DATA_TYPE_BVECS) {
		ceph_msg_data_add_bvecs(msg, &osd_data->bvec_pos);
	} else {
		BUG_ON(osd_data->type != CEPH_OSD_DATA_TYPE_NONE);
	}
}