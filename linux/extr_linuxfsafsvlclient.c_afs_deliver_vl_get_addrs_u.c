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
typedef  int u32 ;
struct afs_uuid__xdr {int dummy; } ;
struct afs_call {int unmarshall; int count; int count2; int /*<<< orphan*/  offset; int /*<<< orphan*/ * buffer; struct afs_addr_list** reply; } ;
struct afs_addr_list {int version; int nr_addrs; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_FS_PORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FS_SERVICE ; 
 int /*<<< orphan*/  _enter (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 struct afs_addr_list* afs_alloc_addrlist (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_merge_fs_addr4 (struct afs_addr_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,unsigned int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_vl_get_addrs_u(struct afs_call *call)
{
	struct afs_addr_list *alist;
	__be32 *bp;
	u32 uniquifier, nentries, count;
	int i, ret;

	_enter("{%u,%zu/%u}", call->unmarshall, call->offset, call->count);

again:
	switch (call->unmarshall) {
	case 0:
		call->offset = 0;
		call->unmarshall++;

		/* Extract the returned uuid, uniquifier, nentries and blkaddrs size */
	case 1:
		ret = afs_extract_data(call, call->buffer,
				       sizeof(struct afs_uuid__xdr) + 3 * sizeof(__be32),
				       true);
		if (ret < 0)
			return ret;

		bp = call->buffer + sizeof(struct afs_uuid__xdr);
		uniquifier	= ntohl(*bp++);
		nentries	= ntohl(*bp++);
		count		= ntohl(*bp);

		nentries = min(nentries, count);
		alist = afs_alloc_addrlist(nentries, FS_SERVICE, AFS_FS_PORT);
		if (!alist)
			return -ENOMEM;
		alist->version = uniquifier;
		call->reply[0] = alist;
		call->count = count;
		call->count2 = nentries;
		call->offset = 0;
		call->unmarshall++;

		/* Extract entries */
	case 2:
		count = min(call->count, 4U);
		ret = afs_extract_data(call, call->buffer,
				       count * sizeof(__be32),
				       call->count > 4);
		if (ret < 0)
			return ret;

		alist = call->reply[0];
		bp = call->buffer;
		for (i = 0; i < count; i++)
			if (alist->nr_addrs < call->count2)
				afs_merge_fs_addr4(alist, *bp++, AFS_FS_PORT);

		call->count -= count;
		if (call->count > 0)
			goto again;
		call->offset = 0;
		call->unmarshall++;
		break;
	}

	_leave(" = 0 [done]");
	return 0;
}