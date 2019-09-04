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
struct usbhs_priv {int dummy; } ;
struct usbhs_pkt {int length; int zero; void (* done ) (struct usbhs_priv*,struct usbhs_pkt*) ;int sequence; scalar_t__ actual; int /*<<< orphan*/ * handler; void* buf; struct usbhs_pipe* pipe; int /*<<< orphan*/  node; } ;
struct usbhs_pipe {int /*<<< orphan*/ * handler; int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbhs_lock (struct usbhs_priv*,unsigned long) ; 
 struct usbhs_priv* usbhs_pipe_to_priv (struct usbhs_pipe*) ; 
 struct device* usbhs_priv_to_dev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhs_unlock (struct usbhs_priv*,unsigned long) ; 
 int /*<<< orphan*/  usbhsf_null_handler ; 

void usbhs_pkt_push(struct usbhs_pipe *pipe, struct usbhs_pkt *pkt,
		    void (*done)(struct usbhs_priv *priv,
				 struct usbhs_pkt *pkt),
		    void *buf, int len, int zero, int sequence)
{
	struct usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	struct device *dev = usbhs_priv_to_dev(priv);
	unsigned long flags;

	if (!done) {
		dev_err(dev, "no done function\n");
		return;
	}

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	if (!pipe->handler) {
		dev_err(dev, "no handler function\n");
		pipe->handler = &usbhsf_null_handler;
	}

	list_move_tail(&pkt->node, &pipe->list);

	/*
	 * each pkt must hold own handler.
	 * because handler might be changed by its situation.
	 * dma handler -> pio handler.
	 */
	pkt->pipe	= pipe;
	pkt->buf	= buf;
	pkt->handler	= pipe->handler;
	pkt->length	= len;
	pkt->zero	= zero;
	pkt->actual	= 0;
	pkt->done	= done;
	pkt->sequence	= sequence;

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/
}