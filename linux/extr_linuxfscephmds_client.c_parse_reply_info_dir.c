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
typedef  int u16 ;
struct ceph_mds_reply_lease {int dummy; } ;
struct ceph_mds_reply_info_parsed {int dir_end; int dir_complete; int hash_order; int offset_hash; scalar_t__ dir_entries; unsigned long dir_buf_size; scalar_t__ dir_nr; TYPE_1__* dir_dir; } ;
struct ceph_mds_reply_dir_entry {int name_len; scalar_t__ offset; int /*<<< orphan*/  inode; void* lease; void* name; } ;
typedef  int /*<<< orphan*/  num ;
struct TYPE_2__ {int /*<<< orphan*/  ndist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_READDIR_FRAG_COMPLETE ; 
 int CEPH_READDIR_FRAG_END ; 
 int CEPH_READDIR_HASH_ORDER ; 
 int CEPH_READDIR_OFFSET_HASH ; 
 int EIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bad ; 
 int ceph_decode_16 (void**) ; 
 void* ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int,void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int parse_reply_info_in (void**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int parse_reply_info_dir(void **p, void *end,
				struct ceph_mds_reply_info_parsed *info,
				u64 features)
{
	u32 num, i = 0;
	int err;

	info->dir_dir = *p;
	if (*p + sizeof(*info->dir_dir) > end)
		goto bad;
	*p += sizeof(*info->dir_dir) +
		sizeof(u32)*le32_to_cpu(info->dir_dir->ndist);
	if (*p > end)
		goto bad;

	ceph_decode_need(p, end, sizeof(num) + 2, bad);
	num = ceph_decode_32(p);
	{
		u16 flags = ceph_decode_16(p);
		info->dir_end = !!(flags & CEPH_READDIR_FRAG_END);
		info->dir_complete = !!(flags & CEPH_READDIR_FRAG_COMPLETE);
		info->hash_order = !!(flags & CEPH_READDIR_HASH_ORDER);
		info->offset_hash = !!(flags & CEPH_READDIR_OFFSET_HASH);
	}
	if (num == 0)
		goto done;

	BUG_ON(!info->dir_entries);
	if ((unsigned long)(info->dir_entries + num) >
	    (unsigned long)info->dir_entries + info->dir_buf_size) {
		pr_err("dir contents are larger than expected\n");
		WARN_ON(1);
		goto bad;
	}

	info->dir_nr = num;
	while (num) {
		struct ceph_mds_reply_dir_entry *rde = info->dir_entries + i;
		/* dentry */
		ceph_decode_need(p, end, sizeof(u32)*2, bad);
		rde->name_len = ceph_decode_32(p);
		ceph_decode_need(p, end, rde->name_len, bad);
		rde->name = *p;
		*p += rde->name_len;
		dout("parsed dir dname '%.*s'\n", rde->name_len, rde->name);
		rde->lease = *p;
		*p += sizeof(struct ceph_mds_reply_lease);

		/* inode */
		err = parse_reply_info_in(p, end, &rde->inode, features);
		if (err < 0)
			goto out_bad;
		/* ceph_readdir_prepopulate() will update it */
		rde->offset = 0;
		i++;
		num--;
	}

done:
	if (*p != end)
		goto bad;
	return 0;

bad:
	err = -EIO;
out_bad:
	pr_err("problem parsing dir contents %d\n", err);
	return err;
}