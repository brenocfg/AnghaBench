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
struct TYPE_7__ {int vid; int vnode; int unique; } ;
struct TYPE_6__ {int tv_sec; } ;
struct TYPE_8__ {TYPE_2__ i_mtime; } ;
struct TYPE_5__ {scalar_t__ data_version; } ;
struct afs_vnode {TYPE_3__ fid; TYPE_4__ vfs_inode; TYPE_1__ status; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_call {unsigned int first_offset; unsigned int last_to; int send_pages; int /*<<< orphan*/ * request; scalar_t__ expected_version; scalar_t__ last; scalar_t__ first; struct afs_vnode** reply; struct address_space* mapping; int /*<<< orphan*/  key; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AFS_SET_MTIME ; 
 int ENOMEM ; 
 int FSSTOREDATA ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  _debug (char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  afs_RXFSStoreData ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,int,int) ; 
 int afs_fs_store_data64 (struct afs_fs_cursor*,struct address_space*,scalar_t__,scalar_t__,unsigned int,unsigned int,int,int,int) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 void* htonl (int) ; 
 int i_size_read (TYPE_4__*) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,TYPE_3__*) ; 

int afs_fs_store_data(struct afs_fs_cursor *fc, struct address_space *mapping,
		      pgoff_t first, pgoff_t last,
		      unsigned offset, unsigned to)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	loff_t size, pos, i_size;
	__be32 *bp;

	_enter(",%x,{%x:%u},,",
	       key_serial(fc->key), vnode->fid.vid, vnode->fid.vnode);

	size = (loff_t)to - (loff_t)offset;
	if (first != last)
		size += (loff_t)(last - first) << PAGE_SHIFT;
	pos = (loff_t)first << PAGE_SHIFT;
	pos += offset;

	i_size = i_size_read(&vnode->vfs_inode);
	if (pos + size > i_size)
		i_size = size + pos;

	_debug("size %llx, at %llx, i_size %llx",
	       (unsigned long long) size, (unsigned long long) pos,
	       (unsigned long long) i_size);

	if (pos >> 32 || i_size >> 32 || size >> 32 || (pos + size) >> 32)
		return afs_fs_store_data64(fc, mapping, first, last, offset, to,
					   size, pos, i_size);

	call = afs_alloc_flat_call(net, &afs_RXFSStoreData,
				   (4 + 6 + 3) * 4,
				   (21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->mapping = mapping;
	call->reply[0] = vnode;
	call->first = first;
	call->last = last;
	call->first_offset = offset;
	call->last_to = to;
	call->send_pages = true;
	call->expected_version = vnode->status.data_version + 1;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);

	*bp++ = htonl(AFS_SET_MTIME); /* mask */
	*bp++ = htonl(vnode->vfs_inode.i_mtime.tv_sec); /* mtime */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonl(pos);
	*bp++ = htonl(size);
	*bp++ = htonl(i_size);

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &vnode->fid);
	return afs_make_call(&fc->ac, call, GFP_NOFS, false);
}