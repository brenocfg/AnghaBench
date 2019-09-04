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
struct afs_volsync {void* type; void* expiry; void* version; TYPE_1__ fid; } ;
struct afs_vnode {void* type; void* expiry; void* version; TYPE_1__ fid; } ;
struct afs_file_status {void* type; void* expiry; void* version; TYPE_1__ fid; } ;
struct afs_callback {void* type; void* expiry; void* version; TYPE_1__ fid; } ;
struct afs_call {size_t count; int /*<<< orphan*/  expected_version; int /*<<< orphan*/ * buffer; struct afs_volsync** reply; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_decode_status (struct afs_call*,int /*<<< orphan*/  const**,struct afs_volsync*,struct afs_volsync*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int afs_transfer_reply (struct afs_call*) ; 
 void* ntohl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  xdr_decode_AFSCallBack (struct afs_call*,struct afs_volsync*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  xdr_decode_AFSVolSync (int /*<<< orphan*/  const**,struct afs_volsync*) ; 

__attribute__((used)) static int afs_deliver_fs_fetch_status(struct afs_call *call)
{
	struct afs_file_status *status = call->reply[1];
	struct afs_callback *callback = call->reply[2];
	struct afs_volsync *volsync = call->reply[3];
	struct afs_vnode *vnode = call->reply[0];
	const __be32 *bp;
	int ret;

	ret = afs_transfer_reply(call);
	if (ret < 0)
		return ret;

	_enter("{%x:%u}", vnode->fid.vid, vnode->fid.vnode);

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	afs_decode_status(call, &bp, status, vnode,
			  &call->expected_version, NULL);
	callback[call->count].version	= ntohl(bp[0]);
	callback[call->count].expiry	= ntohl(bp[1]);
	callback[call->count].type	= ntohl(bp[2]);
	if (vnode)
		xdr_decode_AFSCallBack(call, vnode, &bp);
	else
		bp += 3;
	if (volsync)
		xdr_decode_AFSVolSync(&bp, volsync);

	_leave(" = 0 [done]");
	return 0;
}