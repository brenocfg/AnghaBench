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
struct afs_net {int dummy; } ;
struct afs_call_type {int /*<<< orphan*/  op; } ;
struct afs_call {size_t request_size; size_t reply_max; int /*<<< orphan*/  waitq; int /*<<< orphan*/  operation_ID; void* buffer; void* request; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct afs_call* afs_alloc_call (struct afs_net*,struct afs_call_type const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_extract_to_buf (struct afs_call*,size_t) ; 
 int /*<<< orphan*/  afs_put_call (struct afs_call*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 

struct afs_call *afs_alloc_flat_call(struct afs_net *net,
				     const struct afs_call_type *type,
				     size_t request_size, size_t reply_max)
{
	struct afs_call *call;

	call = afs_alloc_call(net, type, GFP_NOFS);
	if (!call)
		goto nomem_call;

	if (request_size) {
		call->request_size = request_size;
		call->request = kmalloc(request_size, GFP_NOFS);
		if (!call->request)
			goto nomem_free;
	}

	if (reply_max) {
		call->reply_max = reply_max;
		call->buffer = kmalloc(reply_max, GFP_NOFS);
		if (!call->buffer)
			goto nomem_free;
	}

	afs_extract_to_buf(call, call->reply_max);
	call->operation_ID = type->op;
	init_waitqueue_head(&call->waitq);
	return call;

nomem_free:
	afs_put_call(call);
nomem_call:
	return NULL;
}