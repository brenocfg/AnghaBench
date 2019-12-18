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
struct afs_call {TYPE_1__* kvec; int /*<<< orphan*/  iter; } ;
struct TYPE_2__ {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,size_t) ; 

__attribute__((used)) static inline void afs_extract_begin(struct afs_call *call, void *buf, size_t size)
{
	call->kvec[0].iov_base = buf;
	call->kvec[0].iov_len = size;
	iov_iter_kvec(&call->iter, READ, call->kvec, 1, size);
}