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
struct svc_rdma_write_info {TYPE_2__ wi_cc; int /*<<< orphan*/ * wi_segs; int /*<<< orphan*/  wi_nsegs; scalar_t__ wi_seg_no; scalar_t__ wi_seg_off; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ *) ; 
 struct svc_rdma_write_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_cc_init (struct svcxprt_rdma*,TYPE_2__*) ; 
 int /*<<< orphan*/  svc_rdma_write_done ; 

__attribute__((used)) static struct svc_rdma_write_info *
svc_rdma_write_info_alloc(struct svcxprt_rdma *rdma, __be32 *chunk)
{
	struct svc_rdma_write_info *info;

	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return info;

	info->wi_seg_off = 0;
	info->wi_seg_no = 0;
	info->wi_nsegs = be32_to_cpup(++chunk);
	info->wi_segs = ++chunk;
	svc_rdma_cc_init(rdma, &info->wi_cc);
	info->wi_cc.cc_cqe.done = svc_rdma_write_done;
	return info;
}