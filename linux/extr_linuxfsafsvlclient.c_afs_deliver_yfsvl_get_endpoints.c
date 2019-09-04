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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int u32 ;
struct afs_call {int unmarshall; int count; int count2; struct afs_addr_list** reply; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  offset; } ;
struct afs_addr_list {int version; scalar_t__ nr_ipv4; scalar_t__ nr_addrs; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_FS_PORT ; 
 int /*<<< orphan*/  EBADMSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FS_SERVICE ; 
#define  YFS_ENDPOINT_IPV4 129 
#define  YFS_ENDPOINT_IPV6 128 
 int YFS_MAXENDPOINTS ; 
 int /*<<< orphan*/  _enter (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 struct afs_addr_list* afs_alloc_addrlist (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  afs_merge_fs_addr4 (struct afs_addr_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_merge_fs_addr6 (struct afs_addr_list*,int /*<<< orphan*/ *,int) ; 
 int afs_protocol_error (struct afs_call*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_yfsvl_get_endpoints(struct afs_call *call)
{
	struct afs_addr_list *alist;
	__be32 *bp;
	u32 uniquifier, size;
	int ret;

	_enter("{%u,%zu/%u,%u}", call->unmarshall, call->offset, call->count, call->count2);

again:
	switch (call->unmarshall) {
	case 0:
		call->offset = 0;
		call->unmarshall = 1;

		/* Extract the returned uuid, uniquifier, fsEndpoints count and
		 * either the first fsEndpoint type or the volEndpoints
		 * count if there are no fsEndpoints. */
	case 1:
		ret = afs_extract_data(call, call->buffer,
				       sizeof(uuid_t) +
				       3 * sizeof(__be32),
				       true);
		if (ret < 0)
			return ret;

		bp = call->buffer + sizeof(uuid_t);
		uniquifier	= ntohl(*bp++);
		call->count	= ntohl(*bp++);
		call->count2	= ntohl(*bp); /* Type or next count */

		if (call->count > YFS_MAXENDPOINTS)
			return afs_protocol_error(call, -EBADMSG);

		alist = afs_alloc_addrlist(call->count, FS_SERVICE, AFS_FS_PORT);
		if (!alist)
			return -ENOMEM;
		alist->version = uniquifier;
		call->reply[0] = alist;
		call->offset = 0;

		if (call->count == 0)
			goto extract_volendpoints;

		call->unmarshall = 2;

		/* Extract fsEndpoints[] entries */
	case 2:
		switch (call->count2) {
		case YFS_ENDPOINT_IPV4:
			size = sizeof(__be32) * (1 + 1 + 1);
			break;
		case YFS_ENDPOINT_IPV6:
			size = sizeof(__be32) * (1 + 4 + 1);
			break;
		default:
			return afs_protocol_error(call, -EBADMSG);
		}

		size += sizeof(__be32);
		ret = afs_extract_data(call, call->buffer, size, true);
		if (ret < 0)
			return ret;

		alist = call->reply[0];
		bp = call->buffer;
		switch (call->count2) {
		case YFS_ENDPOINT_IPV4:
			if (ntohl(bp[0]) != sizeof(__be32) * 2)
				return afs_protocol_error(call, -EBADMSG);
			afs_merge_fs_addr4(alist, bp[1], ntohl(bp[2]));
			bp += 3;
			break;
		case YFS_ENDPOINT_IPV6:
			if (ntohl(bp[0]) != sizeof(__be32) * 5)
				return afs_protocol_error(call, -EBADMSG);
			afs_merge_fs_addr6(alist, bp + 1, ntohl(bp[5]));
			bp += 6;
			break;
		default:
			return afs_protocol_error(call, -EBADMSG);
		}

		/* Got either the type of the next entry or the count of
		 * volEndpoints if no more fsEndpoints.
		 */
		call->count2 = ntohl(*bp++);

		call->offset = 0;
		call->count--;
		if (call->count > 0)
			goto again;

	extract_volendpoints:
		/* Extract the list of volEndpoints. */
		call->count = call->count2;
		if (!call->count)
			goto end;
		if (call->count > YFS_MAXENDPOINTS)
			return afs_protocol_error(call, -EBADMSG);

		call->unmarshall = 3;

		/* Extract the type of volEndpoints[0].  Normally we would
		 * extract the type of the next endpoint when we extract the
		 * data of the current one, but this is the first...
		 */
	case 3:
		ret = afs_extract_data(call, call->buffer, sizeof(__be32), true);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		call->count2 = ntohl(*bp++);
		call->offset = 0;
		call->unmarshall = 4;

		/* Extract volEndpoints[] entries */
	case 4:
		switch (call->count2) {
		case YFS_ENDPOINT_IPV4:
			size = sizeof(__be32) * (1 + 1 + 1);
			break;
		case YFS_ENDPOINT_IPV6:
			size = sizeof(__be32) * (1 + 4 + 1);
			break;
		default:
			return afs_protocol_error(call, -EBADMSG);
		}

		if (call->count > 1)
			size += sizeof(__be32);
		ret = afs_extract_data(call, call->buffer, size, true);
		if (ret < 0)
			return ret;

		bp = call->buffer;
		switch (call->count2) {
		case YFS_ENDPOINT_IPV4:
			if (ntohl(bp[0]) != sizeof(__be32) * 2)
				return afs_protocol_error(call, -EBADMSG);
			bp += 3;
			break;
		case YFS_ENDPOINT_IPV6:
			if (ntohl(bp[0]) != sizeof(__be32) * 5)
				return afs_protocol_error(call, -EBADMSG);
			bp += 6;
			break;
		default:
			return afs_protocol_error(call, -EBADMSG);
		}

		/* Got either the type of the next entry or the count of
		 * volEndpoints if no more fsEndpoints.
		 */
		call->offset = 0;
		call->count--;
		if (call->count > 0) {
			call->count2 = ntohl(*bp++);
			goto again;
		}

	end:
		call->unmarshall = 5;

		/* Done */
	case 5:
		ret = afs_extract_data(call, call->buffer, 0, false);
		if (ret < 0)
			return ret;
		call->unmarshall = 6;

	case 6:
		break;
	}

	alist = call->reply[0];

	/* Start with IPv6 if available. */
	if (alist->nr_ipv4 < alist->nr_addrs)
		alist->index = alist->nr_ipv4;

	_leave(" = 0 [done]");
	return 0;
}