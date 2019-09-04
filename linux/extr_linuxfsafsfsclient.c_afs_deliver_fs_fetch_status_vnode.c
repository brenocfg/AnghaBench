#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  status; TYPE_1__ fid; } ;
struct afs_call {struct afs_vnode** reply; int /*<<< orphan*/  expected_version; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 scalar_t__ afs_decode_status (struct afs_call*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,struct afs_vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 int afs_transfer_reply (struct afs_call*) ; 
 int /*<<< orphan*/  xdr_decode_AFSCallBack (struct afs_call*,struct afs_vnode*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  xdr_decode_AFSVolSync (int /*<<< orphan*/  const**,struct afs_vnode*) ; 

__attribute__((used)) static int afs_deliver_fs_fetch_status_vnode(struct afs_call *call)
{
	struct afs_vnode *vnode = call->reply[0];
	const __be32 *bp;
	int ret;

	ret = afs_transfer_reply(call);
	if (ret < 0)
		return ret;

	_enter("{%x:%u}", vnode->fid.vid, vnode->fid.vnode);

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	if (afs_decode_status(call, &bp, &vnode->status, vnode,
			      &call->expected_version, NULL) < 0)
		return afs_protocol_error(call, -EBADMSG);
	xdr_decode_AFSCallBack(call, vnode, &bp);
	if (call->reply[1])
		xdr_decode_AFSVolSync(&bp, call->reply[1]);

	_leave(" = 0 [done]");
	return 0;
}