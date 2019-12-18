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
struct afs_call {int unmarshall; unsigned int count2; int /*<<< orphan*/  out_volsync; int /*<<< orphan*/  out_scb; int /*<<< orphan*/ * buffer; struct afs_acl* ret_acl; int /*<<< orphan*/  tmp; } ;
struct afs_acl {unsigned int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_extract_begin (struct afs_call*,int /*<<< orphan*/ ,unsigned int) ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_buf (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_tmp (struct afs_call*) ; 
 int /*<<< orphan*/  data ; 
 struct afs_acl* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 unsigned int round_up (unsigned int,int) ; 
 int /*<<< orphan*/  struct_size (struct afs_acl*,int /*<<< orphan*/ ,unsigned int) ; 
 int xdr_decode_AFSFetchStatus (int /*<<< orphan*/  const**,struct afs_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_decode_AFSVolSync (int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_fs_fetch_acl(struct afs_call *call)
{
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

		/* extract the returned data length */
	case 1:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		size = call->count2 = ntohl(call->tmp);
		size = round_up(size, 4);

		acl = kmalloc(struct_size(acl, data, size), GFP_KERNEL);
		if (!acl)
			return -ENOMEM;
		call->ret_acl = acl;
		acl->size = call->count2;
		afs_extract_begin(call, acl->data, size);
		call->unmarshall++;
		/* Fall through */

		/* extract the returned data */
	case 2:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		afs_extract_to_buf(call, (21 + 6) * 4);
		call->unmarshall++;
		/* Fall through */

		/* extract the metadata */
	case 3:
		ret = afs_extract_data(call, false);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		ret = xdr_decode_AFSFetchStatus(&bp, call, call->out_scb);
		if (ret < 0)
			return ret;
		xdr_decode_AFSVolSync(&bp, call->out_volsync);

		call->unmarshall++;

	case 4:
		break;
	}

	_leave(" = 0 [done]");
	return 0;
}