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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_bvec_iter {int dummy; } ;
struct ceph_osd_data {int /*<<< orphan*/  num_bvecs; struct ceph_bvec_iter bvec_pos; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_DATA_TYPE_BVECS ; 

__attribute__((used)) static void ceph_osd_data_bvecs_init(struct ceph_osd_data *osd_data,
				     struct ceph_bvec_iter *bvec_pos,
				     u32 num_bvecs)
{
	osd_data->type = CEPH_OSD_DATA_TYPE_BVECS;
	osd_data->bvec_pos = *bvec_pos;
	osd_data->num_bvecs = num_bvecs;
}