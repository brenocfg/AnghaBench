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
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct xfs_iext_rec {scalar_t__ lo; scalar_t__ hi; } ;

/* Variables and functions */
 scalar_t__ XFS_IEXT_LENGTH_MASK ; 
 scalar_t__ XFS_IEXT_STARTOFF_MASK ; 

__attribute__((used)) static inline int
xfs_iext_rec_cmp(
	struct xfs_iext_rec	*rec,
	xfs_fileoff_t		offset)
{
	uint64_t		rec_offset = rec->lo & XFS_IEXT_STARTOFF_MASK;
	uint32_t		rec_len = rec->hi & XFS_IEXT_LENGTH_MASK;

	if (rec_offset > offset)
		return 1;
	if (rec_offset + rec_len <= offset)
		return -1;
	return 0;
}