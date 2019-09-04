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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {struct usbhs_pipe* pipe; } ;
struct usbhs_pipe_info {int (* dma_map_ctrl ) (int /*<<< orphan*/ ,struct usbhs_pkt*,int) ;} ;
struct usbhs_pipe {int dummy; } ;
struct usbhs_fifo {int dummy; } ;
struct dma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct usbhs_pkt*,int) ; 
 struct usbhs_fifo* usbhs_pipe_to_fifo (struct usbhs_pipe*) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct usbhs_pipe_info* usbhs_priv_to_pipeinfo (struct usbhs_priv*) ; 
 struct dma_chan* usbhsf_dma_chan_get (struct usbhs_fifo*,struct usbhs_pkt*) ; 

__attribute__((used)) static int __usbhsf_dma_map_ctrl(struct usbhs_pkt *pkt, int map)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
	struct usbhs_fifo *fifo = usbhs_pipe_to_fifo(pipe);
	struct dma_chan *chan = usbhsf_dma_chan_get(fifo, pkt);

	return info->dma_map_ctrl(chan->device->dev, pkt, map);
}