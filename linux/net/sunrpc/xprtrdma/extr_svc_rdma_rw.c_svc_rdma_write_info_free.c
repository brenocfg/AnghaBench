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
struct svc_rdma_write_info {int /*<<< orphan*/  wi_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  kfree (struct svc_rdma_write_info*) ; 
 int /*<<< orphan*/  svc_rdma_cc_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svc_rdma_write_info_free(struct svc_rdma_write_info *info)
{
	svc_rdma_cc_release(&info->wi_cc, DMA_TO_DEVICE);
	kfree(info);
}