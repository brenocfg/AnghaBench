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
struct svcxprt_rdma {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct TYPE_4__ {TYPE_1__ cc_cqe; } ;
struct svc_rdma_read_info {TYPE_2__ ri_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct svc_rdma_read_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_cc_init (struct svcxprt_rdma*,TYPE_2__*) ; 
 int /*<<< orphan*/  svc_rdma_wc_read_done ; 

__attribute__((used)) static struct svc_rdma_read_info *
svc_rdma_read_info_alloc(struct svcxprt_rdma *rdma)
{
	struct svc_rdma_read_info *info;

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return info;

	svc_rdma_cc_init(rdma, &info->ri_cc);
	info->ri_cc.cc_cqe.done = svc_rdma_wc_read_done;
	return info;
}