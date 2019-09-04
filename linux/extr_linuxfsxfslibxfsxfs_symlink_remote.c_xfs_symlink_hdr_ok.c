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
typedef  scalar_t__ uint32_t ;
struct xfs_dsymlink_hdr {int /*<<< orphan*/  sl_owner; int /*<<< orphan*/  sl_bytes; int /*<<< orphan*/  sl_offset; } ;
struct xfs_buf {struct xfs_dsymlink_hdr* b_addr; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 

bool
xfs_symlink_hdr_ok(
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	struct xfs_buf		*bp)
{
	struct xfs_dsymlink_hdr *dsl = bp->b_addr;

	if (offset != be32_to_cpu(dsl->sl_offset))
		return false;
	if (size != be32_to_cpu(dsl->sl_bytes))
		return false;
	if (ino != be64_to_cpu(dsl->sl_owner))
		return false;

	/* ok */
	return true;
}