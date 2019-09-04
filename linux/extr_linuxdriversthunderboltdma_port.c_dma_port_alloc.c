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
typedef  int /*<<< orphan*/  u32 ;
struct tb_switch {int dummy; } ;
struct tb_dma_port {int port; int /*<<< orphan*/  base; struct tb_switch* sw; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PORT_CAP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAIL_DATA_DWORDS ; 
 int dma_find_port (struct tb_switch*) ; 
 int /*<<< orphan*/  kfree (struct tb_dma_port*) ; 
 int /*<<< orphan*/  kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct tb_dma_port* kzalloc (int,int /*<<< orphan*/ ) ; 

struct tb_dma_port *dma_port_alloc(struct tb_switch *sw)
{
	struct tb_dma_port *dma;
	int port;

	port = dma_find_port(sw);
	if (port < 0)
		return NULL;

	dma = kzalloc(sizeof(*dma), GFP_KERNEL);
	if (!dma)
		return NULL;

	dma->buf = kmalloc_array(MAIL_DATA_DWORDS, sizeof(u32), GFP_KERNEL);
	if (!dma->buf) {
		kfree(dma);
		return NULL;
	}

	dma->sw = sw;
	dma->port = port;
	dma->base = DMA_PORT_CAP;

	return dma;
}