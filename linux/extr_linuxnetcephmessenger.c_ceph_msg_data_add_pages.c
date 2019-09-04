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
struct page {int dummy; } ;
struct ceph_msg_data {size_t length; size_t alignment; int /*<<< orphan*/  links; struct page** pages; } ;
struct ceph_msg {size_t data_length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_MSG_DATA_PAGES ; 
 size_t PAGE_MASK ; 
 struct ceph_msg_data* ceph_msg_data_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ceph_msg_data_add_pages(struct ceph_msg *msg, struct page **pages,
		size_t length, size_t alignment)
{
	struct ceph_msg_data *data;

	BUG_ON(!pages);
	BUG_ON(!length);

	data = ceph_msg_data_create(CEPH_MSG_DATA_PAGES);
	BUG_ON(!data);
	data->pages = pages;
	data->length = length;
	data->alignment = alignment & ~PAGE_MASK;

	list_add_tail(&data->links, &msg->data);
	msg->data_length += length;
}