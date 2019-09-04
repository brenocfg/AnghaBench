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
struct smbd_connection {unsigned int reassembly_data_length; scalar_t__ transport_status; int /*<<< orphan*/  wait_reassembly_queue; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 scalar_t__ SMBD_CONNECTED ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  log_read (int /*<<< orphan*/ ,char*,struct page*,char*,unsigned int) ; 
 int smbd_recv_buf (struct smbd_connection*,char*,unsigned int) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smbd_recv_page(struct smbd_connection *info,
		struct page *page, unsigned int page_offset,
		unsigned int to_read)
{
	int ret;
	char *to_address;
	void *page_address;

	/* make sure we have the page ready for read */
	ret = wait_event_interruptible(
		info->wait_reassembly_queue,
		info->reassembly_data_length >= to_read ||
			info->transport_status != SMBD_CONNECTED);
	if (ret)
		return ret;

	/* now we can read from reassembly queue and not sleep */
	page_address = kmap_atomic(page);
	to_address = (char *) page_address + page_offset;

	log_read(INFO, "reading from page=%p address=%p to_read=%d\n",
		page, to_address, to_read);

	ret = smbd_recv_buf(info, to_address, to_read);
	kunmap_atomic(page_address);

	return ret;
}