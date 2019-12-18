#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; } ;
struct xfs_attr_shortform {TYPE_4__ hdr; struct xfs_attr_sf_entry* list; } ;
typedef  struct xfs_attr_shortform xfs_attr_shortform_t ;
struct xfs_da_args {size_t namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; TYPE_3__* dp; } ;
struct xfs_attr_sf_entry {size_t namelen; int /*<<< orphan*/  valuelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_2__* i_afp; } ;
struct TYPE_5__ {scalar_t__ if_data; } ;
struct TYPE_6__ {scalar_t__ if_flags; TYPE_1__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOATTR ; 
 struct xfs_attr_sf_entry* XFS_ATTR_SF_NEXTENTRY (struct xfs_attr_sf_entry*) ; 
 scalar_t__ XFS_IFINLINE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int xfs_attr_copy_value (struct xfs_da_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_attr_namesp_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
xfs_attr_shortform_getvalue(
	struct xfs_da_args	*args)
{
	struct xfs_attr_shortform *sf;
	struct xfs_attr_sf_entry *sfe;
	int			i;

	ASSERT(args->dp->i_afp->if_flags == XFS_IFINLINE);
	sf = (xfs_attr_shortform_t *)args->dp->i_afp->if_u1.if_data;
	sfe = &sf->list[0];
	for (i = 0; i < sf->hdr.count;
				sfe = XFS_ATTR_SF_NEXTENTRY(sfe), i++) {
		if (sfe->namelen != args->namelen)
			continue;
		if (memcmp(args->name, sfe->nameval, args->namelen) != 0)
			continue;
		if (!xfs_attr_namesp_match(args->flags, sfe->flags))
			continue;
		return xfs_attr_copy_value(args, &sfe->nameval[args->namelen],
						sfe->valuelen);
	}
	return -ENOATTR;
}