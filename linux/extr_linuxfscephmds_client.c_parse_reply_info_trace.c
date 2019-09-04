#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ceph_mds_reply_info_parsed {int /*<<< orphan*/  targeti; TYPE_2__* head; void* dlease; int /*<<< orphan*/  dname_len; void* dname; TYPE_1__* dirfrag; int /*<<< orphan*/  diri; } ;
struct TYPE_4__ {scalar_t__ is_target; scalar_t__ is_dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  ndist; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int parse_reply_info_in (void**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_reply_info_trace(void **p, void *end,
				  struct ceph_mds_reply_info_parsed *info,
				  u64 features)
{
	int err;

	if (info->head->is_dentry) {
		err = parse_reply_info_in(p, end, &info->diri, features);
		if (err < 0)
			goto out_bad;

		if (unlikely(*p + sizeof(*info->dirfrag) > end))
			goto bad;
		info->dirfrag = *p;
		*p += sizeof(*info->dirfrag) +
			sizeof(u32)*le32_to_cpu(info->dirfrag->ndist);
		if (unlikely(*p > end))
			goto bad;

		ceph_decode_32_safe(p, end, info->dname_len, bad);
		ceph_decode_need(p, end, info->dname_len, bad);
		info->dname = *p;
		*p += info->dname_len;
		info->dlease = *p;
		*p += sizeof(*info->dlease);
	}

	if (info->head->is_target) {
		err = parse_reply_info_in(p, end, &info->targeti, features);
		if (err < 0)
			goto out_bad;
	}

	if (unlikely(*p != end))
		goto bad;
	return 0;

bad:
	err = -EIO;
out_bad:
	pr_err("problem parsing mds trace %d\n", err);
	return err;
}