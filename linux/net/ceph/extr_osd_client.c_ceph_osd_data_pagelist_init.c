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
struct ceph_pagelist {int dummy; } ;
struct ceph_osd_data {struct ceph_pagelist* pagelist; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_DATA_TYPE_PAGELIST ; 

__attribute__((used)) static void ceph_osd_data_pagelist_init(struct ceph_osd_data *osd_data,
			struct ceph_pagelist *pagelist)
{
	osd_data->type = CEPH_OSD_DATA_TYPE_PAGELIST;
	osd_data->pagelist = pagelist;
}