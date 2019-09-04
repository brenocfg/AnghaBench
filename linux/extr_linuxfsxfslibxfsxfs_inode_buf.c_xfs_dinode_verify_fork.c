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
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct xfs_mount {int dummy; } ;
struct xfs_dinode {int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXAEXTNUM ; 
 int /*<<< orphan*/  MAXEXTNUM ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int XFS_ATTR_FORK ; 
 int XFS_DATA_FORK ; 
 int XFS_DFORK_FORMAT (struct xfs_dinode*,int) ; 
 int /*<<< orphan*/  XFS_DFORK_MAXEXT (struct xfs_dinode*,struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_DFORK_NEXTENTS (struct xfs_dinode*,int) ; 
 int /*<<< orphan*/  XFS_DFORK_SIZE (struct xfs_dinode*,struct xfs_mount*,int) ; 
#define  XFS_DINODE_FMT_BTREE 130 
#define  XFS_DINODE_FMT_EXTENTS 129 
#define  XFS_DINODE_FMT_LOCAL 128 
 int /*<<< orphan*/ * __this_address ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dinode_verify_fork(
	struct xfs_dinode	*dip,
	struct xfs_mount	*mp,
	int			whichfork)
{
	uint32_t		di_nextents = XFS_DFORK_NEXTENTS(dip, whichfork);

	switch (XFS_DFORK_FORMAT(dip, whichfork)) {
	case XFS_DINODE_FMT_LOCAL:
		/*
		 * no local regular files yet
		 */
		if (whichfork == XFS_DATA_FORK) {
			if (S_ISREG(be16_to_cpu(dip->di_mode)))
				return __this_address;
			if (be64_to_cpu(dip->di_size) >
					XFS_DFORK_SIZE(dip, mp, whichfork))
				return __this_address;
		}
		if (di_nextents)
			return __this_address;
		break;
	case XFS_DINODE_FMT_EXTENTS:
		if (di_nextents > XFS_DFORK_MAXEXT(dip, mp, whichfork))
			return __this_address;
		break;
	case XFS_DINODE_FMT_BTREE:
		if (whichfork == XFS_ATTR_FORK) {
			if (di_nextents > MAXAEXTNUM)
				return __this_address;
		} else if (di_nextents > MAXEXTNUM) {
			return __this_address;
		}
		break;
	default:
		return __this_address;
	}
	return NULL;
}