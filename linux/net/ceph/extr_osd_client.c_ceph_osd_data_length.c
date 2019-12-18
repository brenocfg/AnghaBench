#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/  bi_size; } ;
struct TYPE_6__ {TYPE_2__ iter; } ;
struct ceph_osd_data {int type; TYPE_3__ bvec_pos; int /*<<< orphan*/  bio_length; TYPE_1__* pagelist; int /*<<< orphan*/  length; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
#define  CEPH_OSD_DATA_TYPE_BIO 132 
#define  CEPH_OSD_DATA_TYPE_BVECS 131 
#define  CEPH_OSD_DATA_TYPE_NONE 130 
#define  CEPH_OSD_DATA_TYPE_PAGELIST 129 
#define  CEPH_OSD_DATA_TYPE_PAGES 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

__attribute__((used)) static u64 ceph_osd_data_length(struct ceph_osd_data *osd_data)
{
	switch (osd_data->type) {
	case CEPH_OSD_DATA_TYPE_NONE:
		return 0;
	case CEPH_OSD_DATA_TYPE_PAGES:
		return osd_data->length;
	case CEPH_OSD_DATA_TYPE_PAGELIST:
		return (u64)osd_data->pagelist->length;
#ifdef CONFIG_BLOCK
	case CEPH_OSD_DATA_TYPE_BIO:
		return (u64)osd_data->bio_length;
#endif /* CONFIG_BLOCK */
	case CEPH_OSD_DATA_TYPE_BVECS:
		return osd_data->bvec_pos.iter.bi_size;
	default:
		WARN(true, "unrecognized data type %d\n", (int)osd_data->type);
		return 0;
	}
}