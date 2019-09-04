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
typedef  size_t u32 ;
struct qcom_glink_pipe {int dummy; } ;
struct TYPE_2__ {size_t length; } ;
struct glink_smem_pipe {TYPE_1__ native; int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; void* fifo; int /*<<< orphan*/  remote_pid; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 int /*<<< orphan*/  SMEM_GLINK_NATIVE_XPRT_FIFO_1 ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 void* qcom_smem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 struct glink_smem_pipe* to_smem_pipe (struct qcom_glink_pipe*) ; 

__attribute__((used)) static size_t glink_smem_rx_avail(struct qcom_glink_pipe *np)
{
	struct glink_smem_pipe *pipe = to_smem_pipe(np);
	size_t len;
	void *fifo;
	u32 head;
	u32 tail;

	if (!pipe->fifo) {
		fifo = qcom_smem_get(pipe->remote_pid,
				     SMEM_GLINK_NATIVE_XPRT_FIFO_1, &len);
		if (IS_ERR(fifo)) {
			pr_err("failed to acquire RX fifo handle: %ld\n",
			       PTR_ERR(fifo));
			return 0;
		}

		pipe->fifo = fifo;
		pipe->native.length = len;
	}

	head = le32_to_cpu(*pipe->head);
	tail = le32_to_cpu(*pipe->tail);

	if (head < tail)
		return pipe->native.length - tail + head;
	else
		return head - tail;
}