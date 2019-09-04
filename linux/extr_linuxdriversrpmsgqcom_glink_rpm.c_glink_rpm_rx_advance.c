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
struct glink_rpm_pipe {int /*<<< orphan*/  tail; TYPE_1__ native; } ;

/* Variables and functions */
 unsigned int readl (int /*<<< orphan*/ ) ; 
 struct glink_rpm_pipe* to_rpm_pipe (struct qcom_glink_pipe*) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void glink_rpm_rx_advance(struct qcom_glink_pipe *glink_pipe,
				 size_t count)
{
	struct glink_rpm_pipe *pipe = to_rpm_pipe(glink_pipe);
	unsigned int tail;

	tail = readl(pipe->tail);

	tail += count;
	if (tail >= pipe->native.length)
		tail -= pipe->native.length;

	writel(tail, pipe->tail);
}