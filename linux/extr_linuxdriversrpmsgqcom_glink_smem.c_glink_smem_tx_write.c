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
struct qcom_glink_pipe {int dummy; } ;
struct TYPE_2__ {unsigned int length; } ;
struct glink_smem_pipe {int /*<<< orphan*/ * head; TYPE_1__ native; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int glink_smem_tx_write_one (struct glink_smem_pipe*,unsigned int,void const*,size_t) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct glink_smem_pipe* to_smem_pipe (struct qcom_glink_pipe*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void glink_smem_tx_write(struct qcom_glink_pipe *glink_pipe,
				const void *hdr, size_t hlen,
				const void *data, size_t dlen)
{
	struct glink_smem_pipe *pipe = to_smem_pipe(glink_pipe);
	unsigned int head;

	head = le32_to_cpu(*pipe->head);

	head = glink_smem_tx_write_one(pipe, head, hdr, hlen);
	head = glink_smem_tx_write_one(pipe, head, data, dlen);

	/* Ensure head is always aligned to 8 bytes */
	head = ALIGN(head, 8);
	if (head >= pipe->native.length)
		head -= pipe->native.length;

	/* Ensure ordering of fifo and head update */
	wmb();

	*pipe->head = cpu_to_le32(head);
}