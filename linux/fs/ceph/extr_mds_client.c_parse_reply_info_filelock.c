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
typedef  int /*<<< orphan*/  u64 ;
struct ceph_mds_reply_info_parsed {void* filelock_reply; } ;

/* Variables and functions */
 int EIO ; 

__attribute__((used)) static int parse_reply_info_filelock(void **p, void *end,
				     struct ceph_mds_reply_info_parsed *info,
				     u64 features)
{
	if (*p + sizeof(*info->filelock_reply) > end)
		goto bad;

	info->filelock_reply = *p;

	/* Skip over any unrecognized fields */
	*p = end;
	return 0;
bad:
	return -EIO;
}