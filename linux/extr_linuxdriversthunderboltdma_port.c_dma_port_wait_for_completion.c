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
typedef  int u32 ;
struct tb_switch {TYPE_1__* tb; } ;
struct tb_dma_port {scalar_t__ base; int /*<<< orphan*/  port; struct tb_switch* sw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MAIL_IN ; 
 int MAIL_IN_OP_REQUEST ; 
 int dma_port_read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dma_port_wait_for_completion(struct tb_dma_port *dma,
					unsigned int timeout)
{
	unsigned long end = jiffies + msecs_to_jiffies(timeout);
	struct tb_switch *sw = dma->sw;

	do {
		int ret;
		u32 in;

		ret = dma_port_read(sw->tb->ctl, &in, tb_route(sw), dma->port,
				    dma->base + MAIL_IN, 1, 50);
		if (ret) {
			if (ret != -ETIMEDOUT)
				return ret;
		} else if (!(in & MAIL_IN_OP_REQUEST)) {
			return 0;
		}

		usleep_range(50, 100);
	} while (time_before(jiffies, end));

	return -ETIMEDOUT;
}