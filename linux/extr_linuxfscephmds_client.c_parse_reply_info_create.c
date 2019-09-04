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
typedef  int u64 ;
struct ceph_mds_reply_info_parsed {int has_create_ino; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int CEPH_FEATURE_REPLY_CREATE_INODE ; 
 int EIO ; 
 int /*<<< orphan*/  ceph_decode_64 (void**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int parse_reply_info_create(void **p, void *end,
				  struct ceph_mds_reply_info_parsed *info,
				  u64 features)
{
	if (features & CEPH_FEATURE_REPLY_CREATE_INODE) {
		if (*p == end) {
			info->has_create_ino = false;
		} else {
			info->has_create_ino = true;
			info->ino = ceph_decode_64(p);
		}
	}

	if (unlikely(*p != end))
		goto bad;
	return 0;

bad:
	return -EIO;
}