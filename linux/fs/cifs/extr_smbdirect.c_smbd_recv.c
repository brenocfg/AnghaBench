#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct smbd_connection {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_7__ {scalar_t__ count; TYPE_2__* bvec; TYPE_1__* kvec; } ;
struct msghdr {TYPE_3__ msg_iter; } ;
struct TYPE_6__ {unsigned int bv_offset; unsigned int bv_len; struct page* bv_page; } ;
struct TYPE_5__ {char* iov_base; unsigned int iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ITER_BVEC 129 
#define  ITER_KVEC 128 
 int /*<<< orphan*/  VFS ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int iov_iter_rw (TYPE_3__*) ; 
 int iov_iter_type (TYPE_3__*) ; 
 int smbd_recv_buf (struct smbd_connection*,char*,unsigned int) ; 
 int smbd_recv_page (struct smbd_connection*,struct page*,unsigned int,unsigned int) ; 

int smbd_recv(struct smbd_connection *info, struct msghdr *msg)
{
	char *buf;
	struct page *page;
	unsigned int to_read, page_offset;
	int rc;

	if (iov_iter_rw(&msg->msg_iter) == WRITE) {
		/* It's a bug in upper layer to get there */
		cifs_dbg(VFS, "CIFS: invalid msg iter dir %u\n",
			 iov_iter_rw(&msg->msg_iter));
		rc = -EINVAL;
		goto out;
	}

	switch (iov_iter_type(&msg->msg_iter)) {
	case ITER_KVEC:
		buf = msg->msg_iter.kvec->iov_base;
		to_read = msg->msg_iter.kvec->iov_len;
		rc = smbd_recv_buf(info, buf, to_read);
		break;

	case ITER_BVEC:
		page = msg->msg_iter.bvec->bv_page;
		page_offset = msg->msg_iter.bvec->bv_offset;
		to_read = msg->msg_iter.bvec->bv_len;
		rc = smbd_recv_page(info, page, page_offset, to_read);
		break;

	default:
		/* It's a bug in upper layer to get there */
		cifs_dbg(VFS, "CIFS: invalid msg type %d\n",
			 iov_iter_type(&msg->msg_iter));
		rc = -EINVAL;
	}

out:
	/* SMBDirect will read it all or nothing */
	if (rc > 0)
		msg->msg_iter.count = 0;
	return rc;
}