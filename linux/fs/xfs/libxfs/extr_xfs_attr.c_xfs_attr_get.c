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
typedef  int /*<<< orphan*/  uint ;
struct xfs_inode {int /*<<< orphan*/  i_mount; } ;
struct xfs_da_args {unsigned char* value; int valuelen; int /*<<< orphan*/  op_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ATTR_ALLOC ; 
 int ATTR_KERNOVAL ; 
 int EIO ; 
 int /*<<< orphan*/  XFS_DA_OP_ALLOCVAL ; 
 int /*<<< orphan*/  XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (unsigned char*) ; 
 int xfs_attr_args_init (struct xfs_da_args*,struct xfs_inode*,unsigned char const*,int) ; 
 int xfs_attr_get_ilocked (struct xfs_inode*,struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_ilock_attr_map_shared (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_attr_get ; 

int
xfs_attr_get(
	struct xfs_inode	*ip,
	const unsigned char	*name,
	unsigned char		**value,
	int			*valuelenp,
	int			flags)
{
	struct xfs_da_args	args;
	uint			lock_mode;
	int			error;

	ASSERT((flags & (ATTR_ALLOC | ATTR_KERNOVAL)) || *value);

	XFS_STATS_INC(ip->i_mount, xs_attr_get);

	if (XFS_FORCED_SHUTDOWN(ip->i_mount))
		return -EIO;

	error = xfs_attr_args_init(&args, ip, name, flags);
	if (error)
		return error;

	/* Entirely possible to look up a name which doesn't exist */
	args.op_flags = XFS_DA_OP_OKNOENT;
	if (flags & ATTR_ALLOC)
		args.op_flags |= XFS_DA_OP_ALLOCVAL;
	else
		args.value = *value;
	args.valuelen = *valuelenp;

	lock_mode = xfs_ilock_attr_map_shared(ip);
	error = xfs_attr_get_ilocked(ip, &args);
	xfs_iunlock(ip, lock_mode);
	*valuelenp = args.valuelen;

	/* on error, we have to clean up allocated value buffers */
	if (error) {
		if (flags & ATTR_ALLOC) {
			kmem_free(args.value);
			*value = NULL;
		}
		return error;
	}
	*value = args.value;
	return 0;
}