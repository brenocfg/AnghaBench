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
struct svc_rdma_write_info {int /*<<< orphan*/  wi_base; } ;
struct kvec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int svc_rdma_build_writes (struct svc_rdma_write_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_vec_to_sg ; 

__attribute__((used)) static int svc_rdma_send_xdr_kvec(struct svc_rdma_write_info *info,
				  struct kvec *vec)
{
	info->wi_base = vec->iov_base;
	return svc_rdma_build_writes(info, svc_rdma_vec_to_sg,
				     vec->iov_len);
}