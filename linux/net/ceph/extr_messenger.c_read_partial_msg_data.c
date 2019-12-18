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
typedef  void* u32 ;
struct page {int dummy; } ;
struct ceph_msg_data_cursor {int /*<<< orphan*/  resid; scalar_t__ total_resid; } ;
struct ceph_msg {int /*<<< orphan*/  num_data_items; struct ceph_msg_data_cursor cursor; } ;
struct ceph_connection {void* in_data_crc; int /*<<< orphan*/  sock; int /*<<< orphan*/  msgr; struct ceph_msg* in_msg; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NOCRC ; 
 void* ceph_crc32c_page (void*,struct page*,size_t,int) ; 
 int /*<<< orphan*/  ceph_msg_data_advance (struct ceph_msg_data_cursor*,size_t) ; 
 struct page* ceph_msg_data_next (struct ceph_msg_data_cursor*,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int ceph_tcp_recvpage (int /*<<< orphan*/ ,struct page*,size_t,size_t) ; 
 int /*<<< orphan*/  ceph_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_msgr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_partial_msg_data(struct ceph_connection *con)
{
	struct ceph_msg *msg = con->in_msg;
	struct ceph_msg_data_cursor *cursor = &msg->cursor;
	bool do_datacrc = !ceph_test_opt(from_msgr(con->msgr), NOCRC);
	struct page *page;
	size_t page_offset;
	size_t length;
	u32 crc = 0;
	int ret;

	if (!msg->num_data_items)
		return -EIO;

	if (do_datacrc)
		crc = con->in_data_crc;
	while (cursor->total_resid) {
		if (!cursor->resid) {
			ceph_msg_data_advance(cursor, 0);
			continue;
		}

		page = ceph_msg_data_next(cursor, &page_offset, &length, NULL);
		ret = ceph_tcp_recvpage(con->sock, page, page_offset, length);
		if (ret <= 0) {
			if (do_datacrc)
				con->in_data_crc = crc;

			return ret;
		}

		if (do_datacrc)
			crc = ceph_crc32c_page(crc, page, page_offset, ret);
		ceph_msg_data_advance(cursor, (size_t)ret);
	}
	if (do_datacrc)
		con->in_data_crc = crc;

	return 1;	/* must return > 0 to indicate success */
}