#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct uart_port {TYPE_2__* state; } ;
struct TYPE_13__ {TYPE_5__* dram; scalar_t__ statStg_pci; int /*<<< orphan*/ * xmitRestart; TYPE_4__* statStg; int /*<<< orphan*/ * xmit_buf; } ;
struct TYPE_12__ {int /*<<< orphan*/  StartXmitCmd; int /*<<< orphan*/  CmdReg; } ;
struct TYPE_11__ {TYPE_3__* xmit; } ;
struct TYPE_10__ {unsigned long flags; int leLength; } ;
struct TYPE_8__ {int tail; int head; int /*<<< orphan*/ * buf; } ;
struct TYPE_9__ {TYPE_1__ xmit; } ;

/* Variables and functions */
 unsigned char CMD_XMIT_RCV_ENABLE ; 
 TYPE_6__* ICOM_PORT ; 
 int SA_FLAGS_READY_TO_XMIT ; 
 unsigned char START_XMIT ; 
 int UART_XMIT_SIZE ; 
 unsigned long XMIT_BUFF_SZ ; 
 int cpu_to_le16 (unsigned long) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (TYPE_6__*,char*,unsigned long) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int icom_write(struct uart_port *port)
{
	unsigned long data_count;
	unsigned char cmdReg;
	unsigned long offset;
	int temp_tail = port->state->xmit.tail;

	trace(ICOM_PORT, "WRITE", 0);

	if (cpu_to_le16(ICOM_PORT->statStg->xmit[0].flags) &
	    SA_FLAGS_READY_TO_XMIT) {
		trace(ICOM_PORT, "WRITE_FULL", 0);
		return 0;
	}

	data_count = 0;
	while ((port->state->xmit.head != temp_tail) &&
	       (data_count <= XMIT_BUFF_SZ)) {

		ICOM_PORT->xmit_buf[data_count++] =
		    port->state->xmit.buf[temp_tail];

		temp_tail++;
		temp_tail &= (UART_XMIT_SIZE - 1);
	}

	if (data_count) {
		ICOM_PORT->statStg->xmit[0].flags =
		    cpu_to_le16(SA_FLAGS_READY_TO_XMIT);
		ICOM_PORT->statStg->xmit[0].leLength =
		    cpu_to_le16(data_count);
		offset =
		    (unsigned long) &ICOM_PORT->statStg->xmit[0] -
		    (unsigned long) ICOM_PORT->statStg;
		*ICOM_PORT->xmitRestart =
		    cpu_to_le32(ICOM_PORT->statStg_pci + offset);
		cmdReg = readb(&ICOM_PORT->dram->CmdReg);
		writeb(cmdReg | CMD_XMIT_RCV_ENABLE,
		       &ICOM_PORT->dram->CmdReg);
		writeb(START_XMIT, &ICOM_PORT->dram->StartXmitCmd);
		trace(ICOM_PORT, "WRITE_START", data_count);
		/* write flush */
		readb(&ICOM_PORT->dram->StartXmitCmd);
	}

	return data_count;
}