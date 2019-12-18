#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct yfs_xdr_YFSVolSync {int dummy; } ;
struct yfs_xdr_YFSFetchStatus {int dummy; } ;
struct yfs_acl {int flags; void* num_cleaned; void* inherit_flag; struct afs_acl* vol_acl; struct afs_acl* acl; } ;
struct afs_call {int unmarshall; unsigned int count2; int /*<<< orphan*/  out_volsync; int /*<<< orphan*/  out_scb; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  tmp; struct yfs_acl* out_yacl; } ;
struct afs_acl {unsigned int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int YFS_ACL_WANT_ACL ; 
 int YFS_ACL_WANT_VOL_ACL ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_extract_begin (struct afs_call*,int /*<<< orphan*/ ,unsigned int) ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_discard (struct afs_call*,unsigned int) ; 
 int /*<<< orphan*/  afs_extract_to_buf (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_tmp (struct afs_call*) ; 
 int /*<<< orphan*/  data ; 
 struct afs_acl* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 unsigned int round_up (unsigned int,int) ; 
 int /*<<< orphan*/  struct_size (struct afs_acl*,int /*<<< orphan*/ ,unsigned int) ; 
 int xdr_decode_YFSFetchStatus (int /*<<< orphan*/  const**,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_decode_YFSVolSync (int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yfs_deliver_fs_fetch_opaque_acl(struct afs_call *call)
{
	struct yfs_acl *yacl = call->out_yacl;
	struct afs_acl *acl;
	const __be32 *bp;
	unsigned int size;
	int ret;

	_enter("{%u}", call->unmarshall);

	switch (call->unmarshall) {
	case 0:
		afs_extract_to_tmp(call);
		call->unmarshall++;
		/* Fall through */

		/* Extract the file ACL length */
	case 1:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		size = call->count2 = ntohl(call->tmp);
		size = round_up(size, 4);

		if (yacl->flags & YFS_ACL_WANT_ACL) {
			acl = kmalloc(struct_size(acl, data, size), GFP_KERNEL);
			if (!acl)
				return -ENOMEM;
			yacl->acl = acl;
			acl->size = call->count2;
			afs_extract_begin(call, acl->data, size);
		} else {
			afs_extract_discard(call, size);
		}
		call->unmarshall++;
		/* Fall through */

		/* Extract the file ACL */
	case 2:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		afs_extract_to_tmp(call);
		call->unmarshall++;
		/* Fall through */

		/* Extract the volume ACL length */
	case 3:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		size = call->count2 = ntohl(call->tmp);
		size = round_up(size, 4);

		if (yacl->flags & YFS_ACL_WANT_VOL_ACL) {
			acl = kmalloc(struct_size(acl, data, size), GFP_KERNEL);
			if (!acl)
				return -ENOMEM;
			yacl->vol_acl = acl;
			acl->size = call->count2;
			afs_extract_begin(call, acl->data, size);
		} else {
			afs_extract_discard(call, size);
		}
		call->unmarshall++;
		/* Fall through */

		/* Extract the volume ACL */
	case 4:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		afs_extract_to_buf(call,
				   sizeof(__be32) * 2 +
				   sizeof(struct yfs_xdr_YFSFetchStatus) +
				   sizeof(struct yfs_xdr_YFSVolSync));
		call->unmarshall++;
		/* Fall through */

		/* extract the metadata */
	case 5:
		ret = afs_extract_data(call, false);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		yacl->inherit_flag = ntohl(*bp++);
		yacl->num_cleaned = ntohl(*bp++);
		ret = xdr_decode_YFSFetchStatus(&bp, call, call->out_scb);
		if (ret < 0)
			return ret;
		xdr_decode_YFSVolSync(&bp, call->out_volsync);

		call->unmarshall++;
		/* Fall through */

	case 6:
		break;
	}

	_leave(" = 0 [done]");
	return 0;
}