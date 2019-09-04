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
typedef  int u8 ;
typedef  int u32 ;
struct yenta_socket {int /*<<< orphan*/  socket; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CB_CD1EVENT ; 
 int CB_CD2EVENT ; 
 int /*<<< orphan*/  CB_SOCKET_EVENT ; 
 int /*<<< orphan*/  I365_CSC ; 
 int I365_CSC_BVD1 ; 
 int I365_CSC_BVD2 ; 
 int I365_CSC_DETECT ; 
 int I365_CSC_READY ; 
 int I365_CSC_STSCHG ; 
 int /*<<< orphan*/  I365_INTCTL ; 
 int I365_PC_IOCARD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int SS_BATDEAD ; 
 unsigned int SS_BATWARN ; 
 unsigned int SS_DETECT ; 
 unsigned int SS_READY ; 
 unsigned int SS_STSCHG ; 
 int cb_readl (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_writel (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int exca_readb (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static irqreturn_t yenta_interrupt(int irq, void *dev_id)
{
	unsigned int events;
	struct yenta_socket *socket = (struct yenta_socket *) dev_id;
	u8 csc;
	u32 cb_event;

	/* Clear interrupt status for the event */
	cb_event = cb_readl(socket, CB_SOCKET_EVENT);
	cb_writel(socket, CB_SOCKET_EVENT, cb_event);

	csc = exca_readb(socket, I365_CSC);

	if (!(cb_event || csc))
		return IRQ_NONE;

	events = (cb_event & (CB_CD1EVENT | CB_CD2EVENT)) ? SS_DETECT : 0 ;
	events |= (csc & I365_CSC_DETECT) ? SS_DETECT : 0;
	if (exca_readb(socket, I365_INTCTL) & I365_PC_IOCARD) {
		events |= (csc & I365_CSC_STSCHG) ? SS_STSCHG : 0;
	} else {
		events |= (csc & I365_CSC_BVD1) ? SS_BATDEAD : 0;
		events |= (csc & I365_CSC_BVD2) ? SS_BATWARN : 0;
		events |= (csc & I365_CSC_READY) ? SS_READY : 0;
	}

	if (events)
		pcmcia_parse_events(&socket->socket, events);

	return IRQ_HANDLED;
}