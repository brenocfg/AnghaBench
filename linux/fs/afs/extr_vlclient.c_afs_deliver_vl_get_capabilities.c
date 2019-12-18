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
struct afs_call {int unmarshall; int count; int count2; int /*<<< orphan*/  tmp; int /*<<< orphan*/  _iter; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int afs_extract_data (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_discard (struct afs_call*,int) ; 
 int /*<<< orphan*/  afs_extract_to_tmp (struct afs_call*) ; 
 int /*<<< orphan*/  iov_iter_count (int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_vl_get_capabilities(struct afs_call *call)
{
	u32 count;
	int ret;

	_enter("{%u,%zu/%u}",
	       call->unmarshall, iov_iter_count(call->_iter), call->count);

	switch (call->unmarshall) {
	case 0:
		afs_extract_to_tmp(call);
		call->unmarshall++;

		/* Fall through - and extract the capabilities word count */
	case 1:
		ret = afs_extract_data(call, true);
		if (ret < 0)
			return ret;

		count = ntohl(call->tmp);
		call->count = count;
		call->count2 = count;

		call->unmarshall++;
		afs_extract_discard(call, count * sizeof(__be32));

		/* Fall through - and extract capabilities words */
	case 2:
		ret = afs_extract_data(call, false);
		if (ret < 0)
			return ret;

		/* TODO: Examine capabilities */

		call->unmarshall++;
		break;
	}

	_leave(" = 0 [done]");
	return 0;
}