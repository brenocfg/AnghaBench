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
typedef  scalar_t__ u32 ;
struct qcom_glink_pipe {int dummy; } ;
struct TYPE_2__ {scalar_t__ length; } ;
struct glink_smem_pipe {int /*<<< orphan*/ * tail; TYPE_1__ native; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct glink_smem_pipe* to_smem_pipe (struct qcom_glink_pipe*) ; 

__attribute__((used)) static void glink_smem_rx_advance(struct qcom_glink_pipe *np,
				  size_t count)
{
	struct glink_smem_pipe *pipe = to_smem_pipe(np);
	u32 tail;

	tail = le32_to_cpu(*pipe->tail);

	tail += count;
	if (tail > pipe->native.length)
		tail -= pipe->native.length;

	*pipe->tail = cpu_to_le32(tail);
}