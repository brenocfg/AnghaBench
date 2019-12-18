#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  i_mount; TYPE_3__* i_afp; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_23__ {int count; } ;
struct TYPE_26__ {TYPE_2__ hdr; TYPE_7__* list; } ;
typedef  TYPE_5__ xfs_attr_shortform_t ;
struct TYPE_27__ {int entno; scalar_t__ hash; int namelen; int valuelen; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
typedef  TYPE_6__ xfs_attr_sf_sort_t ;
struct TYPE_28__ {int namelen; int valuelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  nameval; } ;
typedef  TYPE_7__ xfs_attr_sf_entry_t ;
struct TYPE_29__ {scalar_t__ bufsize; scalar_t__ seen_enough; int /*<<< orphan*/  (* put_listent ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;TYPE_4__* dp; TYPE_9__* cursor; } ;
typedef  TYPE_8__ xfs_attr_list_context_t ;
struct TYPE_30__ {int initted; scalar_t__ hashval; int offset; scalar_t__ blkno; } ;
typedef  TYPE_9__ attrlist_cursor_kern_t ;
struct TYPE_22__ {scalar_t__ if_data; } ;
struct TYPE_24__ {scalar_t__ if_bytes; TYPE_1__ if_u1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  KM_NOFS ; 
 TYPE_7__* XFS_ATTR_SF_NEXTENTRY (TYPE_7__*) ; 
 int /*<<< orphan*/  XFS_CORRUPTION_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 scalar_t__ XFS_ISRESET_CURSOR (TYPE_9__*) ; 
 TYPE_6__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_list_sf (TYPE_8__*) ; 
 int /*<<< orphan*/  trace_xfs_attr_list_sf_all (TYPE_8__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfs_attr_shortform_compare ; 
 scalar_t__ xfs_da_hashname (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_sort (TYPE_6__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_attr_shortform_list(xfs_attr_list_context_t *context)
{
	attrlist_cursor_kern_t *cursor;
	xfs_attr_sf_sort_t *sbuf, *sbp;
	xfs_attr_shortform_t *sf;
	xfs_attr_sf_entry_t *sfe;
	xfs_inode_t *dp;
	int sbsize, nsbuf, count, i;

	ASSERT(context != NULL);
	dp = context->dp;
	ASSERT(dp != NULL);
	ASSERT(dp->i_afp != NULL);
	sf = (xfs_attr_shortform_t *)dp->i_afp->if_u1.if_data;
	ASSERT(sf != NULL);
	if (!sf->hdr.count)
		return 0;
	cursor = context->cursor;
	ASSERT(cursor != NULL);

	trace_xfs_attr_list_sf(context);

	/*
	 * If the buffer is large enough and the cursor is at the start,
	 * do not bother with sorting since we will return everything in
	 * one buffer and another call using the cursor won't need to be
	 * made.
	 * Note the generous fudge factor of 16 overhead bytes per entry.
	 * If bufsize is zero then put_listent must be a search function
	 * and can just scan through what we have.
	 */
	if (context->bufsize == 0 ||
	    (XFS_ISRESET_CURSOR(cursor) &&
	     (dp->i_afp->if_bytes + sf->hdr.count * 16) < context->bufsize)) {
		for (i = 0, sfe = &sf->list[0]; i < sf->hdr.count; i++) {
			context->put_listent(context,
					     sfe->flags,
					     sfe->nameval,
					     (int)sfe->namelen,
					     (int)sfe->valuelen);
			/*
			 * Either search callback finished early or
			 * didn't fit it all in the buffer after all.
			 */
			if (context->seen_enough)
				break;
			sfe = XFS_ATTR_SF_NEXTENTRY(sfe);
		}
		trace_xfs_attr_list_sf_all(context);
		return 0;
	}

	/* do no more for a search callback */
	if (context->bufsize == 0)
		return 0;

	/*
	 * It didn't all fit, so we have to sort everything on hashval.
	 */
	sbsize = sf->hdr.count * sizeof(*sbuf);
	sbp = sbuf = kmem_alloc(sbsize, KM_NOFS);

	/*
	 * Scan the attribute list for the rest of the entries, storing
	 * the relevant info from only those that match into a buffer.
	 */
	nsbuf = 0;
	for (i = 0, sfe = &sf->list[0]; i < sf->hdr.count; i++) {
		if (unlikely(
		    ((char *)sfe < (char *)sf) ||
		    ((char *)sfe >= ((char *)sf + dp->i_afp->if_bytes)))) {
			XFS_CORRUPTION_ERROR("xfs_attr_shortform_list",
					     XFS_ERRLEVEL_LOW,
					     context->dp->i_mount, sfe,
					     sizeof(*sfe));
			kmem_free(sbuf);
			return -EFSCORRUPTED;
		}

		sbp->entno = i;
		sbp->hash = xfs_da_hashname(sfe->nameval, sfe->namelen);
		sbp->name = sfe->nameval;
		sbp->namelen = sfe->namelen;
		/* These are bytes, and both on-disk, don't endian-flip */
		sbp->valuelen = sfe->valuelen;
		sbp->flags = sfe->flags;
		sfe = XFS_ATTR_SF_NEXTENTRY(sfe);
		sbp++;
		nsbuf++;
	}

	/*
	 * Sort the entries on hash then entno.
	 */
	xfs_sort(sbuf, nsbuf, sizeof(*sbuf), xfs_attr_shortform_compare);

	/*
	 * Re-find our place IN THE SORTED LIST.
	 */
	count = 0;
	cursor->initted = 1;
	cursor->blkno = 0;
	for (sbp = sbuf, i = 0; i < nsbuf; i++, sbp++) {
		if (sbp->hash == cursor->hashval) {
			if (cursor->offset == count) {
				break;
			}
			count++;
		} else if (sbp->hash > cursor->hashval) {
			break;
		}
	}
	if (i == nsbuf) {
		kmem_free(sbuf);
		return 0;
	}

	/*
	 * Loop putting entries into the user buffer.
	 */
	for ( ; i < nsbuf; i++, sbp++) {
		if (cursor->hashval != sbp->hash) {
			cursor->hashval = sbp->hash;
			cursor->offset = 0;
		}
		context->put_listent(context,
				     sbp->flags,
				     sbp->name,
				     sbp->namelen,
				     sbp->valuelen);
		if (context->seen_enough)
			break;
		cursor->offset++;
	}

	kmem_free(sbuf);
	return 0;
}