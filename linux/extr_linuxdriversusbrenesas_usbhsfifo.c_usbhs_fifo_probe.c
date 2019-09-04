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
struct usbhs_fifo {char* name; int /*<<< orphan*/  ctr; int /*<<< orphan*/  sel; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIFO ; 
 int /*<<< orphan*/  CFIFOCTR ; 
 int /*<<< orphan*/  CFIFOSEL ; 
 int /*<<< orphan*/  USBHS_DFIFO_INIT (struct usbhs_priv*,struct usbhs_fifo*,int) ; 
 int /*<<< orphan*/  USBHS_DFIFO_INIT_NO_PORT (struct usbhs_priv*,struct usbhs_fifo*,int) ; 
 struct usbhs_fifo* usbhsf_get_cfifo (struct usbhs_priv*) ; 

int usbhs_fifo_probe(struct usbhs_priv *priv)
{
	struct usbhs_fifo *fifo;

	/* CFIFO */
	fifo = usbhsf_get_cfifo(priv);
	fifo->name	= "CFIFO";
	fifo->port	= CFIFO;
	fifo->sel	= CFIFOSEL;
	fifo->ctr	= CFIFOCTR;

	/* DFIFO */
	USBHS_DFIFO_INIT(priv, fifo, 0);
	USBHS_DFIFO_INIT(priv, fifo, 1);
	USBHS_DFIFO_INIT_NO_PORT(priv, fifo, 2);
	USBHS_DFIFO_INIT_NO_PORT(priv, fifo, 3);

	return 0;
}