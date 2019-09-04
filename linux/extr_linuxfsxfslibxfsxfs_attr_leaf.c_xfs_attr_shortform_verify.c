#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct TYPE_4__ {scalar_t__ di_aformat; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct TYPE_5__ {scalar_t__ if_data; } ;
struct xfs_ifork {int if_bytes; TYPE_2__ if_u1; } ;
struct TYPE_6__ {int count; } ;
struct xfs_attr_shortform {TYPE_3__ hdr; struct xfs_attr_sf_entry* list; } ;
struct xfs_attr_sf_hdr {int dummy; } ;
struct xfs_attr_sf_entry {scalar_t__ namelen; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int XFS_ATTR_NSP_ONDISK_MASK ; 
 struct xfs_attr_sf_entry* XFS_ATTR_SF_NEXTENTRY (struct xfs_attr_sf_entry*) ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __this_address ; 
 int hweight8 (int) ; 

xfs_failaddr_t
xfs_attr_shortform_verify(
	struct xfs_inode		*ip)
{
	struct xfs_attr_shortform	*sfp;
	struct xfs_attr_sf_entry	*sfep;
	struct xfs_attr_sf_entry	*next_sfep;
	char				*endp;
	struct xfs_ifork		*ifp;
	int				i;
	int				size;

	ASSERT(ip->i_d.di_aformat == XFS_DINODE_FMT_LOCAL);
	ifp = XFS_IFORK_PTR(ip, XFS_ATTR_FORK);
	sfp = (struct xfs_attr_shortform *)ifp->if_u1.if_data;
	size = ifp->if_bytes;

	/*
	 * Give up if the attribute is way too short.
	 */
	if (size < sizeof(struct xfs_attr_sf_hdr))
		return __this_address;

	endp = (char *)sfp + size;

	/* Check all reported entries */
	sfep = &sfp->list[0];
	for (i = 0; i < sfp->hdr.count; i++) {
		/*
		 * struct xfs_attr_sf_entry has a variable length.
		 * Check the fixed-offset parts of the structure are
		 * within the data buffer.
		 */
		if (((char *)sfep + sizeof(*sfep)) >= endp)
			return __this_address;

		/* Don't allow names with known bad length. */
		if (sfep->namelen == 0)
			return __this_address;

		/*
		 * Check that the variable-length part of the structure is
		 * within the data buffer.  The next entry starts after the
		 * name component, so nextentry is an acceptable test.
		 */
		next_sfep = XFS_ATTR_SF_NEXTENTRY(sfep);
		if ((char *)next_sfep > endp)
			return __this_address;

		/*
		 * Check for unknown flags.  Short form doesn't support
		 * the incomplete or local bits, so we can use the namespace
		 * mask here.
		 */
		if (sfep->flags & ~XFS_ATTR_NSP_ONDISK_MASK)
			return __this_address;

		/*
		 * Check for invalid namespace combinations.  We only allow
		 * one namespace flag per xattr, so we can just count the
		 * bits (i.e. hweight) here.
		 */
		if (hweight8(sfep->flags & XFS_ATTR_NSP_ONDISK_MASK) > 1)
			return __this_address;

		sfep = next_sfep;
	}
	if ((void *)sfep != (void *)endp)
		return __this_address;

	return NULL;
}