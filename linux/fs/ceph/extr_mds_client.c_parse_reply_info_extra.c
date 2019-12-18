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
struct ceph_mds_reply_info_parsed {TYPE_1__* head; } ;
struct TYPE_2__ {int /*<<< orphan*/  op; } ;

/* Variables and functions */
 scalar_t__ CEPH_MDS_OP_CREATE ; 
 scalar_t__ CEPH_MDS_OP_GETFILELOCK ; 
 scalar_t__ CEPH_MDS_OP_LSSNAP ; 
 scalar_t__ CEPH_MDS_OP_READDIR ; 
 int EIO ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int parse_reply_info_create (void**,void*,struct ceph_mds_reply_info_parsed*,int /*<<< orphan*/ ) ; 
 int parse_reply_info_filelock (void**,void*,struct ceph_mds_reply_info_parsed*,int /*<<< orphan*/ ) ; 
 int parse_reply_info_readdir (void**,void*,struct ceph_mds_reply_info_parsed*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_reply_info_extra(void **p, void *end,
				  struct ceph_mds_reply_info_parsed *info,
				  u64 features)
{
	u32 op = le32_to_cpu(info->head->op);

	if (op == CEPH_MDS_OP_GETFILELOCK)
		return parse_reply_info_filelock(p, end, info, features);
	else if (op == CEPH_MDS_OP_READDIR || op == CEPH_MDS_OP_LSSNAP)
		return parse_reply_info_readdir(p, end, info, features);
	else if (op == CEPH_MDS_OP_CREATE)
		return parse_reply_info_create(p, end, info, features);
	else
		return -EIO;
}