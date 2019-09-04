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
struct TYPE_4__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct ceph_msg {int /*<<< orphan*/  footer; TYPE_3__* middle; TYPE_1__ front; int /*<<< orphan*/  hdr; int /*<<< orphan*/  data_length; int /*<<< orphan*/  front_alloc_len; } ;
struct TYPE_5__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_6__ {TYPE_2__ vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  pr_debug (char*,struct ceph_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 

void ceph_msg_dump(struct ceph_msg *msg)
{
	pr_debug("msg_dump %p (front_alloc_len %d length %zd)\n", msg,
		 msg->front_alloc_len, msg->data_length);
	print_hex_dump(KERN_DEBUG, "header: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       &msg->hdr, sizeof(msg->hdr), true);
	print_hex_dump(KERN_DEBUG, " front: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       msg->front.iov_base, msg->front.iov_len, true);
	if (msg->middle)
		print_hex_dump(KERN_DEBUG, "middle: ",
			       DUMP_PREFIX_OFFSET, 16, 1,
			       msg->middle->vec.iov_base,
			       msg->middle->vec.iov_len, true);
	print_hex_dump(KERN_DEBUG, "footer: ",
		       DUMP_PREFIX_OFFSET, 16, 1,
		       &msg->footer, sizeof(msg->footer), true);
}