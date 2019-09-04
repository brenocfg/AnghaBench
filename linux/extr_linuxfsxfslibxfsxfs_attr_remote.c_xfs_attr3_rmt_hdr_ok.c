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
typedef  scalar_t__ xfs_ino_t ;
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  scalar_t__ xfs_daddr_t ;
typedef  scalar_t__ uint32_t ;
struct xfs_attr3_rmt_hdr {int /*<<< orphan*/  rm_owner; int /*<<< orphan*/  rm_bytes; int /*<<< orphan*/  rm_offset; int /*<<< orphan*/  rm_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_attr3_rmt_hdr_ok(
	void			*ptr,
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	xfs_daddr_t		bno)
{
	struct xfs_attr3_rmt_hdr *rmt = ptr;

	if (bno != be64_to_cpu(rmt->rm_blkno))
		return __this_address;
	if (offset != be32_to_cpu(rmt->rm_offset))
		return __this_address;
	if (size != be32_to_cpu(rmt->rm_bytes))
		return __this_address;
	if (ino != be64_to_cpu(rmt->rm_owner))
		return __this_address;

	/* ok */
	return NULL;
}