#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t umode_t ;
struct TYPE_9__ {size_t vid; size_t vnode; size_t unique; } ;
struct TYPE_7__ {size_t tv_sec; } ;
struct TYPE_8__ {TYPE_2__ i_mtime; } ;
struct afs_vnode {TYPE_4__ fid; TYPE_3__ vfs_inode; } ;
struct afs_status_cb {int dummy; } ;
struct afs_net {int dummy; } ;
struct afs_fs_cursor {int /*<<< orphan*/  ac; TYPE_5__* cbi; int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_fid {int dummy; } ;
struct afs_call {int /*<<< orphan*/ * request; struct afs_status_cb* out_scb; struct afs_fid* out_fid; struct afs_status_cb* out_dir_scb; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {TYPE_1__* server; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_SERVER_FL_IS_YFS ; 
 size_t AFS_SET_MODE ; 
 size_t AFS_SET_MTIME ; 
 int ENOMEM ; 
 size_t FSCREATEFILE ; 
 size_t FSMAKEDIR ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t S_IALLUGO ; 
 scalar_t__ S_ISDIR (size_t) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXFSCreateFile ; 
 int /*<<< orphan*/  afs_RXFSMakeDir ; 
 struct afs_call* afs_alloc_flat_call (struct afs_net*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_set_fc_call (struct afs_call*,struct afs_fs_cursor*) ; 
 int /*<<< orphan*/  afs_use_fs_server (struct afs_call*,TYPE_5__*) ; 
 struct afs_net* afs_v2net (struct afs_vnode*) ; 
 int afs_wait_for_call_to_complete (struct afs_call*,int /*<<< orphan*/ *) ; 
 void* htonl (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_afs_make_fs_call1 (struct afs_call*,TYPE_4__*,char const*) ; 
 int yfs_fs_create_file (struct afs_fs_cursor*,char const*,size_t,struct afs_status_cb*,struct afs_fid*,struct afs_status_cb*) ; 
 int yfs_fs_make_dir (struct afs_fs_cursor*,char const*,size_t,struct afs_status_cb*,struct afs_fid*,struct afs_status_cb*) ; 

int afs_fs_create(struct afs_fs_cursor *fc,
		  const char *name,
		  umode_t mode,
		  struct afs_status_cb *dvnode_scb,
		  struct afs_fid *newfid,
		  struct afs_status_cb *new_scb)
{
	struct afs_vnode *dvnode = fc->vnode;
	struct afs_call *call;
	struct afs_net *net = afs_v2net(dvnode);
	size_t namesz, reqsz, padsz;
	__be32 *bp;

	if (test_bit(AFS_SERVER_FL_IS_YFS, &fc->cbi->server->flags)){
		if (S_ISDIR(mode))
			return yfs_fs_make_dir(fc, name, mode, dvnode_scb,
					       newfid, new_scb);
		else
			return yfs_fs_create_file(fc, name, mode, dvnode_scb,
						  newfid, new_scb);
	}

	_enter("");

	namesz = strlen(name);
	padsz = (4 - (namesz & 3)) & 3;
	reqsz = (5 * 4) + namesz + padsz + (6 * 4);

	call = afs_alloc_flat_call(
		net, S_ISDIR(mode) ? &afs_RXFSMakeDir : &afs_RXFSCreateFile,
		reqsz, (3 + 21 + 21 + 3 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = fc->key;
	call->out_dir_scb = dvnode_scb;
	call->out_fid = newfid;
	call->out_scb = new_scb;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(S_ISDIR(mode) ? FSMAKEDIR : FSCREATEFILE);
	*bp++ = htonl(dvnode->fid.vid);
	*bp++ = htonl(dvnode->fid.vnode);
	*bp++ = htonl(dvnode->fid.unique);
	*bp++ = htonl(namesz);
	memcpy(bp, name, namesz);
	bp = (void *) bp + namesz;
	if (padsz > 0) {
		memset(bp, 0, padsz);
		bp = (void *) bp + padsz;
	}
	*bp++ = htonl(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonl(dvnode->vfs_inode.i_mtime.tv_sec); /* mtime */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = htonl(mode & S_IALLUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	afs_use_fs_server(call, fc->cbi);
	trace_afs_make_fs_call1(call, &dvnode->fid, name);
	afs_set_fc_call(call, fc);
	afs_make_call(&fc->ac, call, GFP_NOFS);
	return afs_wait_for_call_to_complete(call, &fc->ac);
}