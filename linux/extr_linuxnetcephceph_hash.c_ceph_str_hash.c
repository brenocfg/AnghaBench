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

/* Variables and functions */
#define  CEPH_STR_HASH_LINUX 129 
#define  CEPH_STR_HASH_RJENKINS 128 
 unsigned int ceph_str_hash_linux (char const*,unsigned int) ; 
 unsigned int ceph_str_hash_rjenkins (char const*,unsigned int) ; 

unsigned int ceph_str_hash(int type, const char *s, unsigned int len)
{
	switch (type) {
	case CEPH_STR_HASH_LINUX:
		return ceph_str_hash_linux(s, len);
	case CEPH_STR_HASH_RJENKINS:
		return ceph_str_hash_rjenkins(s, len);
	default:
		return -1;
	}
}