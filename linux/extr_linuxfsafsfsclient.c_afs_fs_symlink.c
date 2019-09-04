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
typedef  scalar_t__ u64 ;
struct TYPE_6__ {size_t vid; size_t vnode; size_t unique; } ;
struct TYPE_4__ {size_t tv_sec; } ;
struct TYPE_5__ {TYPE_1__ i_mtime; } ;
struct afs_vnode {TYPE_3__ fid; TYPE_2__ vfs_inode; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; int /*<<< orphan*/  cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_file_status {TYPE_3__ fid; TYPE_2__ vfs_inode; } ;
struct afs_fid {TYPE_3__ fid; TYPE_2__ vfs_inode; } ;
struct afs_call {int /*<<< orphan*/ * request; scalar_t__ expected_version; struct afs_vnode** reply; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t AFS_SET_MODE ; 
 size_t AFS_SET_MTIME ; 
 int ENOMEM ; 
 size_t FSSYMLINK ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t S_IRWXUGO ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXFSSymlink ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,size_t,int) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,int /*<<< orphan*/ ) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 void* htonl (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call (struct afs_call*,TYPE_3__*) ; 

int afs_fs_symlink(struct afs_fs_cursor *fc,
		   const char *name,
		   const char *contents,
		   u64 current_data_version,
		   struct afs_fid *newfid,
		   struct afs_file_status *newstatus)
{
	struct afs_vnode *vnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(vnode);
	size_t namesz, reqsz, padsz, c_namesz, c_padsz;
	__be32 *bp;

	_enter("");

	namesz = strlen(name);
	padsz = (4 - (namesz & 3)) & 3;

	c_namesz = strlen(contents);
	c_padsz = (4 - (c_namesz & 3)) & 3;

	reqsz = (6 * 4) + namesz + padsz + c_namesz + c_padsz + (6 * 4);

	call = afs_alloc_flat_call(net, &afs_RXFSSymlink, reqsz,
				   (3 + 21 + 21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->reply[0] = vnode;
	call->reply[1] = newfid;
	call->reply[2] = newstatus;
	call->expected_version = current_data_version + 1;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSYMLINK);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);
	*bp++ = htonl(namesz);
	memcpy(bp, name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}
	*bp++ = htonl(c_namesz);
	memcpy(bp, contents, c_namesz);
	bp = (void *) bp + c_namesz;
	if (c_padsz > 0) {
		memset(bp, 0, c_padsz);
		bp = (void *) bp + c_padsz;
	}
	*bp++ = htonl(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonl(vnode->vfs_inode.i_mtime.tv_sec); /* mtime */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = htonl(S_IRWXUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call(call, &vnode->fid);
	return afs_make_call(&fc->ac, call, GFP_NOFS, false);
}