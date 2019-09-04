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
 int /*<<< orphan*/  DMA_PORT_TIMEOUT ; 
 int MAIL_IN_CMD_FLASH_UPDATE_AUTH ; 
 scalar_t__ MAIL_OUT ; 
 int MAIL_OUT_STATUS_CMD_MASK ; 
 int MAIL_OUT_STATUS_CMD_SHIFT ; 
 int MAIL_OUT_STATUS_MASK ; 
 int dma_port_read (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 

int dma_port_flash_update_auth_status(struct tb_dma_port *dma, u32 *status)
{
	struct tb_switch *sw = dma->sw;
	u32 out, cmd;
	int ret;

	ret = dma_port_read(sw->tb->ctl, &out, tb_route(sw), dma->port,
			    dma->base + MAIL_OUT, 1, DMA_PORT_TIMEOUT);
	if (ret)
		return ret;

	/* Check if the status relates to flash update auth */
	cmd = (out & MAIL_OUT_STATUS_CMD_MASK) >> MAIL_OUT_STATUS_CMD_SHIFT;
	if (cmd == MAIL_IN_CMD_FLASH_UPDATE_AUTH) {
		if (status)
			*status = out & MAIL_OUT_STATUS_MASK;

		/* Reset is needed in any case */
		return 1;
	}

	return 0;
}