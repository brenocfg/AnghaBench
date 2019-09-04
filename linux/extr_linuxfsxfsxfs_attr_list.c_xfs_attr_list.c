#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_inode_t ;
struct TYPE_6__ {int resynch; int flags; char* alist; int bufsize; int firstu; int /*<<< orphan*/  put_listent; TYPE_2__* cursor; int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ xfs_attr_list_context_t ;
struct attrlist {int* al_offset; scalar_t__ al_more; scalar_t__ al_count; } ;
typedef  int /*<<< orphan*/  context ;
struct TYPE_7__ {scalar_t__ initted; scalar_t__ offset; scalar_t__ blkno; scalar_t__ hashval; scalar_t__ pad2; scalar_t__ pad1; } ;
typedef  TYPE_2__ attrlist_cursor_kern_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_INCOMPLETE ; 
 int ATTR_KERNOVAL ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int xfs_attr_list_int (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_attr_put_listent ; 

int
xfs_attr_list(
	xfs_inode_t	*dp,
	char		*buffer,
	int		bufsize,
	int		flags,
	attrlist_cursor_kern_t *cursor)
{
	xfs_attr_list_context_t context;
	struct attrlist *alist;
	int error;

	/*
	 * Validate the cursor.
	 */
	if (cursor->pad1 || cursor->pad2)
		return -EINVAL;
	if ((cursor->initted == 0) &&
	    (cursor->hashval || cursor->blkno || cursor->offset))
		return -EINVAL;

	/* Only internal consumers can retrieve incomplete attrs. */
	if (flags & ATTR_INCOMPLETE)
		return -EINVAL;

	/*
	 * Check for a properly aligned buffer.
	 */
	if (((long)buffer) & (sizeof(int)-1))
		return -EFAULT;
	if (flags & ATTR_KERNOVAL)
		bufsize = 0;

	/*
	 * Initialize the output buffer.
	 */
	memset(&context, 0, sizeof(context));
	context.dp = dp;
	context.cursor = cursor;
	context.resynch = 1;
	context.flags = flags;
	context.alist = buffer;
	context.bufsize = (bufsize & ~(sizeof(int)-1));  /* align */
	context.firstu = context.bufsize;
	context.put_listent = xfs_attr_put_listent;

	alist = (struct attrlist *)context.alist;
	alist->al_count = 0;
	alist->al_more = 0;
	alist->al_offset[0] = context.bufsize;

	error = xfs_attr_list_int(&context);
	ASSERT(error <= 0);
	return error;
}