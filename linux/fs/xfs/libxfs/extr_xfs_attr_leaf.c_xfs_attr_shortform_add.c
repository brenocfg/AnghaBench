#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_14__ {int di_forkoff; } ;
struct TYPE_17__ {struct xfs_ifork* i_afp; TYPE_1__ i_d; int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_18__ {size_t namelen; size_t valuelen; int /*<<< orphan*/  trans; int /*<<< orphan*/  value; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; TYPE_4__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_16__ {int count; int /*<<< orphan*/  totsize; } ;
struct TYPE_19__ {TYPE_3__ hdr; TYPE_7__* list; } ;
typedef  TYPE_6__ xfs_attr_shortform_t ;
struct TYPE_20__ {size_t namelen; size_t valuelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  flags; } ;
typedef  TYPE_7__ xfs_attr_sf_entry_t ;
struct TYPE_15__ {scalar_t__ if_data; } ;
struct xfs_ifork {int if_flags; TYPE_2__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_ATTR_NSP_ARGS_TO_ONDISK (int /*<<< orphan*/ ) ; 
 int XFS_ATTR_SF_ENTSIZE_BYNAME (size_t,size_t) ; 
 TYPE_7__* XFS_ATTR_SF_NEXTENTRY (TYPE_7__*) ; 
 int XFS_IFINLINE ; 
 int XFS_ILOG_ADATA ; 
 int XFS_ILOG_CORE ; 
 int /*<<< orphan*/  be16_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  trace_xfs_attr_sf_add (TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_attr_namesp_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sbversion_add_attr2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ ,TYPE_4__*,int) ; 

void
xfs_attr_shortform_add(xfs_da_args_t *args, int forkoff)
{
	xfs_attr_shortform_t *sf;
	xfs_attr_sf_entry_t *sfe;
	int i, offset, size;
	xfs_mount_t *mp;
	xfs_inode_t *dp;
	struct xfs_ifork *ifp;

	trace_xfs_attr_sf_add(args);

	dp = args->dp;
	mp = dp->i_mount;
	dp->i_d.di_forkoff = forkoff;

	ifp = dp->i_afp;
	ASSERT(ifp->if_flags & XFS_IFINLINE);
	sf = (xfs_attr_shortform_t *)ifp->if_u1.if_data;
	sfe = &sf->list[0];
	for (i = 0; i < sf->hdr.count; sfe = XFS_ATTR_SF_NEXTENTRY(sfe), i++) {
#ifdef DEBUG
		if (sfe->namelen != args->namelen)
			continue;
		if (memcmp(args->name, sfe->nameval, args->namelen) != 0)
			continue;
		if (!xfs_attr_namesp_match(args->flags, sfe->flags))
			continue;
		ASSERT(0);
#endif
	}

	offset = (char *)sfe - (char *)sf;
	size = XFS_ATTR_SF_ENTSIZE_BYNAME(args->namelen, args->valuelen);
	xfs_idata_realloc(dp, size, XFS_ATTR_FORK);
	sf = (xfs_attr_shortform_t *)ifp->if_u1.if_data;
	sfe = (xfs_attr_sf_entry_t *)((char *)sf + offset);

	sfe->namelen = args->namelen;
	sfe->valuelen = args->valuelen;
	sfe->flags = XFS_ATTR_NSP_ARGS_TO_ONDISK(args->flags);
	memcpy(sfe->nameval, args->name, args->namelen);
	memcpy(&sfe->nameval[args->namelen], args->value, args->valuelen);
	sf->hdr.count++;
	be16_add_cpu(&sf->hdr.totsize, size);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_ADATA);

	xfs_sbversion_add_attr2(mp, args->trans);
}