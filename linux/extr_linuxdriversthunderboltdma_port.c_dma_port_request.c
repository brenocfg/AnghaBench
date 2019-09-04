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
typedef  int /*<<< orphan*/  u32 ;
struct tb_switch {TYPE_1__* tb; } ;
struct tb_dma_port {scalar_t__ base; int /*<<< orphan*/  port; struct tb_switch* sw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PORT_TIMEOUT ; 
 scalar_t__ MAIL_IN ; 
 scalar_t__ MAIL_OUT ; 
 int dma_port_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int dma_port_wait_for_completion (struct tb_dma_port*,unsigned int) ; 
 int dma_port_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 

__attribute__((used)) static int dma_port_request(struct tb_dma_port *dma, u32 in,
			    unsigned int timeout)
{
	struct tb_switch *sw = dma->sw;
	u32 out;
	int ret;

	ret = dma_port_write(sw->tb->ctl, &in, tb_route(sw), dma->port,
			     dma->base + MAIL_IN, 1, DMA_PORT_TIMEOUT);
	if (ret)
		return ret;

	ret = dma_port_wait_for_completion(dma, timeout);
	if (ret)
		return ret;

	ret = dma_port_read(sw->tb->ctl, &out, tb_route(sw), dma->port,
			    dma->base + MAIL_OUT, 1, DMA_PORT_TIMEOUT);
	if (ret)
		return ret;

	return status_to_errno(out);
}