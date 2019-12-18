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
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct bio_vec {unsigned int bv_len; unsigned int bv_offset; struct page* bv_page; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int cifs_readv_from_socket (struct TCP_Server_Info*,struct msghdr*) ; 
 int /*<<< orphan*/  iov_iter_bvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bio_vec*,int,unsigned int) ; 

int
cifs_read_page_from_socket(struct TCP_Server_Info *server, struct page *page,
	unsigned int page_offset, unsigned int to_read)
{
	struct msghdr smb_msg;
	struct bio_vec bv = {
		.bv_page = page, .bv_len = to_read, .bv_offset = page_offset};
	iov_iter_bvec(&smb_msg.msg_iter, READ, &bv, 1, to_read);
	return cifs_readv_from_socket(server, &smb_msg);
}