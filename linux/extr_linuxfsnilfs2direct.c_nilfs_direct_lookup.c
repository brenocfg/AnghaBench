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
struct nilfs_bmap {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ NILFS_BMAP_INVALID_PTR ; 
 scalar_t__ NILFS_DIRECT_KEY_MAX ; 
 scalar_t__ nilfs_direct_get_ptr (struct nilfs_bmap const*,scalar_t__) ; 

__attribute__((used)) static int nilfs_direct_lookup(const struct nilfs_bmap *direct,
			       __u64 key, int level, __u64 *ptrp)
{
	__u64 ptr;

	if (key > NILFS_DIRECT_KEY_MAX || level != 1)
		return -ENOENT;
	ptr = nilfs_direct_get_ptr(direct, key);
	if (ptr == NILFS_BMAP_INVALID_PTR)
		return -ENOENT;

	*ptrp = ptr;
	return 0;
}