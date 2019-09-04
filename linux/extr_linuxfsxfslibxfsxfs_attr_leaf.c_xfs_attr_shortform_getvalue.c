#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t namelen; int flags; scalar_t__ valuelen; int /*<<< orphan*/  value; int /*<<< orphan*/  name; TYPE_3__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_14__ {int count; } ;
struct TYPE_16__ {TYPE_4__ hdr; TYPE_7__* list; } ;
typedef  TYPE_6__ xfs_attr_shortform_t ;
struct TYPE_17__ {size_t namelen; scalar_t__ valuelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  flags; } ;
typedef  TYPE_7__ xfs_attr_sf_entry_t ;
struct TYPE_13__ {TYPE_2__* i_afp; } ;
struct TYPE_11__ {scalar_t__ if_data; } ;
struct TYPE_12__ {scalar_t__ if_flags; TYPE_1__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOVAL ; 
 int EEXIST ; 
 int ENOATTR ; 
 int ERANGE ; 
 TYPE_7__* XFS_ATTR_SF_NEXTENTRY (TYPE_7__*) ; 
 scalar_t__ XFS_IFINLINE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xfs_attr_namesp_match (int,int /*<<< orphan*/ ) ; 

int
xfs_attr_shortform_getvalue(xfs_da_args_t *args)
{
	xfs_attr_shortform_t *sf;
	xfs_attr_sf_entry_t *sfe;
	int i;

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
		if (args->flags & ATTR_KERNOVAL) {
			args->valuelen = sfe->valuelen;
			return -EEXIST;
		}
		if (args->valuelen < sfe->valuelen) {
			args->valuelen = sfe->valuelen;
			return -ERANGE;
		}
		args->valuelen = sfe->valuelen;
		memcpy(args->value, &sfe->nameval[args->namelen],
						    args->valuelen);
		return -EEXIST;
	}
	return -ENOATTR;
}