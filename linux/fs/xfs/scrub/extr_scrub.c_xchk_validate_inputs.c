#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_scrub_metadata {int sm_flags; size_t sm_type; int /*<<< orphan*/  sm_ino; int /*<<< orphan*/  sm_gen; int /*<<< orphan*/  sm_agno; int /*<<< orphan*/  sm_reserved; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_agcount; } ;
struct xfs_mount {int m_flags; TYPE_1__ m_sb; } ;
struct xchk_meta_ops {int type; int /*<<< orphan*/  (* has ) (TYPE_1__*) ;int /*<<< orphan*/ * scrub; int /*<<< orphan*/ * setup; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int EROFS ; 
#define  ST_FS 131 
#define  ST_INODE 130 
#define  ST_NONE 129 
#define  ST_PERAG 128 
 int XFS_MOUNT_RDONLY ; 
 int XFS_SCRUB_FLAGS_IN ; 
 int XFS_SCRUB_FLAGS_OUT ; 
 int XFS_SCRUB_IFLAG_REPAIR ; 
 size_t XFS_SCRUB_TYPE_NR ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct xchk_meta_ops* meta_scrub_ops ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (TYPE_1__*) ; 

__attribute__((used)) static int
xchk_validate_inputs(
	struct xfs_mount		*mp,
	struct xfs_scrub_metadata	*sm)
{
	int				error;
	const struct xchk_meta_ops	*ops;

	error = -EINVAL;
	/* Check our inputs. */
	sm->sm_flags &= ~XFS_SCRUB_FLAGS_OUT;
	if (sm->sm_flags & ~XFS_SCRUB_FLAGS_IN)
		goto out;
	/* sm_reserved[] must be zero */
	if (memchr_inv(sm->sm_reserved, 0, sizeof(sm->sm_reserved)))
		goto out;

	error = -ENOENT;
	/* Do we know about this type of metadata? */
	if (sm->sm_type >= XFS_SCRUB_TYPE_NR)
		goto out;
	ops = &meta_scrub_ops[sm->sm_type];
	if (ops->setup == NULL || ops->scrub == NULL)
		goto out;
	/* Does this fs even support this type of metadata? */
	if (ops->has && !ops->has(&mp->m_sb))
		goto out;

	error = -EINVAL;
	/* restricting fields must be appropriate for type */
	switch (ops->type) {
	case ST_NONE:
	case ST_FS:
		if (sm->sm_ino || sm->sm_gen || sm->sm_agno)
			goto out;
		break;
	case ST_PERAG:
		if (sm->sm_ino || sm->sm_gen ||
		    sm->sm_agno >= mp->m_sb.sb_agcount)
			goto out;
		break;
	case ST_INODE:
		if (sm->sm_agno || (sm->sm_gen && !sm->sm_ino))
			goto out;
		break;
	default:
		goto out;
	}

	/*
	 * We only want to repair read-write v5+ filesystems.  Defer the check
	 * for ops->repair until after our scrub confirms that we need to
	 * perform repairs so that we avoid failing due to not supporting
	 * repairing an object that doesn't need repairs.
	 */
	if (sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR) {
		error = -EOPNOTSUPP;
		if (!xfs_sb_version_hascrc(&mp->m_sb))
			goto out;

		error = -EROFS;
		if (mp->m_flags & XFS_MOUNT_RDONLY)
			goto out;
	}

	error = 0;
out:
	return error;
}