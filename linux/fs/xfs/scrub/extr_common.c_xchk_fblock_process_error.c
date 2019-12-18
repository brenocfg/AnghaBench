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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_scrub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_SCRUB_OFLAG_CORRUPT ; 
 int /*<<< orphan*/  __return_address ; 
 int __xchk_fblock_process_error (struct xfs_scrub*,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
xchk_fblock_process_error(
	struct xfs_scrub	*sc,
	int			whichfork,
	xfs_fileoff_t		offset,
	int			*error)
{
	return __xchk_fblock_process_error(sc, whichfork, offset, error,
			XFS_SCRUB_OFLAG_CORRUPT, __return_address);
}