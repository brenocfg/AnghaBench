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
struct ceph_osd_request {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __ceph_osdc_alloc_messages (struct ceph_osd_request*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_num_data_items (struct ceph_osd_request*,int*,int*) ; 

int ceph_osdc_alloc_messages(struct ceph_osd_request *req, gfp_t gfp)
{
	int num_request_data_items, num_reply_data_items;

	get_num_data_items(req, &num_request_data_items, &num_reply_data_items);
	return __ceph_osdc_alloc_messages(req, gfp, num_request_data_items,
					  num_reply_data_items);
}