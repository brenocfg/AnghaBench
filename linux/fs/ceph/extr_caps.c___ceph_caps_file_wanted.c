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
struct ceph_inode_info {scalar_t__* i_nr_by_mode; } ;

/* Variables and functions */
 int CEPH_FILE_MODE_BITS ; 
 int ceph_caps_for_mode (int) ; 

int __ceph_caps_file_wanted(struct ceph_inode_info *ci)
{
	int i, bits = 0;
	for (i = 0; i < CEPH_FILE_MODE_BITS; i++) {
		if (ci->i_nr_by_mode[i])
			bits |= 1 << i;
	}
	if (bits == 0)
		return 0;
	return ceph_caps_for_mode(bits >> 1);
}