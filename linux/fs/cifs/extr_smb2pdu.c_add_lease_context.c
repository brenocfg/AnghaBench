#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct smb2_create_req {int /*<<< orphan*/  CreateContextsLength; scalar_t__ CreateContextsOffset; int /*<<< orphan*/  RequestedOplockLevel; } ;
struct kvec {scalar_t__ iov_len; struct smb2_create_req* iov_base; } ;
struct TCP_Server_Info {TYPE_2__* vals; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_4__ {scalar_t__ create_lease_size; } ;
struct TYPE_3__ {struct smb2_create_req* (* create_lease_buf ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_LEASE ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,scalar_t__) ; 
 struct smb2_create_req* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_lease_context(struct TCP_Server_Info *server, struct kvec *iov,
		  unsigned int *num_iovec, u8 *lease_key, __u8 *oplock)
{
	struct smb2_create_req *req = iov[0].iov_base;
	unsigned int num = *num_iovec;

	iov[num].iov_base = server->ops->create_lease_buf(lease_key, *oplock);
	if (iov[num].iov_base == NULL)
		return -ENOMEM;
	iov[num].iov_len = server->vals->create_lease_size;
	req->RequestedOplockLevel = SMB2_OPLOCK_LEVEL_LEASE;
	if (!req->CreateContextsOffset)
		req->CreateContextsOffset = cpu_to_le32(
				sizeof(struct smb2_create_req) +
				iov[num - 1].iov_len);
	le32_add_cpu(&req->CreateContextsLength,
		     server->vals->create_lease_size);
	*num_iovec = num + 1;
	return 0;
}