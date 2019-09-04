#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; TYPE_1__* dp; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct TYPE_13__ {int count; } ;
struct TYPE_15__ {TYPE_3__ hdr; TYPE_6__* list; } ;
typedef  TYPE_5__ xfs_attr_shortform_t ;
struct TYPE_16__ {scalar_t__ namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  nameval; } ;
typedef  TYPE_6__ xfs_attr_sf_entry_t ;
struct TYPE_12__ {scalar_t__ if_data; } ;
struct xfs_ifork {int if_flags; TYPE_2__ if_u1; } ;
struct TYPE_11__ {struct xfs_ifork* i_afp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EEXIST ; 
 int ENOATTR ; 
 TYPE_6__* XFS_ATTR_SF_NEXTENTRY (TYPE_6__*) ; 
 int XFS_IFINLINE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_attr_sf_lookup (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_attr_namesp_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_attr_shortform_lookup(xfs_da_args_t *args)
{
	xfs_attr_shortform_t *sf;
	xfs_attr_sf_entry_t *sfe;
	int i;
	struct xfs_ifork *ifp;

	trace_xfs_attr_sf_lookup(args);

	ifp = args->dp->i_afp;
	ASSERT(ifp->if_flags & XFS_IFINLINE);
	sf = (xfs_attr_shortform_t *)ifp->if_u1.if_data;
	sfe = &sf->list[0];
	for (i = 0; i < sf->hdr.count;
				sfe = XFS_ATTR_SF_NEXTENTRY(sfe), i++) {
		if (sfe->namelen != args->namelen)
			continue;
		if (memcmp(args->name, sfe->nameval, args->namelen) != 0)
			continue;
		if (!xfs_attr_namesp_match(args->flags, sfe->flags))
			continue;
		return -EEXIST;
	}
	return -ENOATTR;
}