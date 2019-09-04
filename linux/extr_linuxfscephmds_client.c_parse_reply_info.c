#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int iov_len; void* iov_base; } ;
struct ceph_msg {TYPE_1__ front; } ;
struct ceph_mds_reply_info_parsed {void* snapblob; scalar_t__ snapblob_len; void* head; } ;
struct ceph_mds_reply_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int parse_reply_info_extra (void**,void*,struct ceph_mds_reply_info_parsed*,int /*<<< orphan*/ ) ; 
 int parse_reply_info_trace (void**,void*,struct ceph_mds_reply_info_parsed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int parse_reply_info(struct ceph_msg *msg,
			    struct ceph_mds_reply_info_parsed *info,
			    u64 features)
{
	void *p, *end;
	u32 len;
	int err;

	info->head = msg->front.iov_base;
	p = msg->front.iov_base + sizeof(struct ceph_mds_reply_head);
	end = p + msg->front.iov_len - sizeof(struct ceph_mds_reply_head);

	/* trace */
	ceph_decode_32_safe(&p, end, len, bad);
	if (len > 0) {
		ceph_decode_need(&p, end, len, bad);
		err = parse_reply_info_trace(&p, p+len, info, features);
		if (err < 0)
			goto out_bad;
	}

	/* extra */
	ceph_decode_32_safe(&p, end, len, bad);
	if (len > 0) {
		ceph_decode_need(&p, end, len, bad);
		err = parse_reply_info_extra(&p, p+len, info, features);
		if (err < 0)
			goto out_bad;
	}

	/* snap blob */
	ceph_decode_32_safe(&p, end, len, bad);
	info->snapblob_len = len;
	info->snapblob = p;
	p += len;

	if (p != end)
		goto bad;
	return 0;

bad:
	err = -EIO;
out_bad:
	pr_err("mds parse_reply err %d\n", err);
	return err;
}