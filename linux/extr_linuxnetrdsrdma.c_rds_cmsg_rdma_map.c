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
struct rds_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  op_rdma_mr; } ;
struct rds_message {scalar_t__ m_rdma_cookie; int /*<<< orphan*/  m_conn_path; TYPE_1__ rdma; } ;
struct rds_get_mr_args {int dummy; } ;
struct cmsghdr {scalar_t__ cmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ CMSG_LEN (int) ; 
 int EINVAL ; 
 int __rds_rdma_map (struct rds_sock*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int rds_cmsg_rdma_map(struct rds_sock *rs, struct rds_message *rm,
			  struct cmsghdr *cmsg)
{
	if (cmsg->cmsg_len < CMSG_LEN(sizeof(struct rds_get_mr_args)) ||
	    rm->m_rdma_cookie != 0)
		return -EINVAL;

	return __rds_rdma_map(rs, CMSG_DATA(cmsg), &rm->m_rdma_cookie,
			      &rm->rdma.op_rdma_mr, rm->m_conn_path);
}