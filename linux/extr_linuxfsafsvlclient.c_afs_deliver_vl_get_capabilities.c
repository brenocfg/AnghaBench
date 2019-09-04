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
struct afs_call {int unmarshall; int count; int count2; scalar_t__ service_id; void** reply; int /*<<< orphan*/  offset; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  tmp; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int afs_extract_data (struct afs_call*,int /*<<< orphan*/ *,int,int) ; 
 int min (int,unsigned int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_deliver_vl_get_capabilities(struct afs_call *call)
{
	u32 count;
	int ret;

	_enter("{%u,%zu/%u}", call->unmarshall, call->offset, call->count);

again:
	switch (call->unmarshall) {
	case 0:
		call->offset = 0;
		call->unmarshall++;

		/* Extract the capabilities word count */
	case 1:
		ret = afs_extract_data(call, &call->tmp,
				       1 * sizeof(__be32),
				       true);
		if (ret < 0)
			return ret;

		count = ntohl(call->tmp);

		call->count = count;
		call->count2 = count;
		call->offset = 0;
		call->unmarshall++;

		/* Extract capabilities words */
	case 2:
		count = min(call->count, 16U);
		ret = afs_extract_data(call, call->buffer,
				       count * sizeof(__be32),
				       call->count > 16);
		if (ret < 0)
			return ret;

		/* TODO: Examine capabilities */

		call->count -= count;
		if (call->count > 0)
			goto again;
		call->offset = 0;
		call->unmarshall++;
		break;
	}

	call->reply[0] = (void *)(unsigned long)call->service_id;

	_leave(" = 0 [done]");
	return 0;
}