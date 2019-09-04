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
struct TYPE_2__ {int /*<<< orphan*/  membase; } ;
struct imx_port {int ucr1; int ucr2; int ucr3; int ucr4; int ufcr; TYPE_1__ port; } ;

/* Variables and functions */
#define  UCR1 132 
#define  UCR2 131 
 int UCR2_SRST ; 
#define  UCR3 130 
#define  UCR4 129 
#define  UFCR 128 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 imx_uart_readl(struct imx_port *sport, u32 offset)
{
	switch (offset) {
	case UCR1:
		return sport->ucr1;
		break;
	case UCR2:
		/*
		 * UCR2_SRST is the only bit in the cached registers that might
		 * differ from the value that was last written. As it only
		 * automatically becomes one after being cleared, reread
		 * conditionally.
		 */
		if (!(sport->ucr2 & UCR2_SRST))
			sport->ucr2 = readl(sport->port.membase + offset);
		return sport->ucr2;
		break;
	case UCR3:
		return sport->ucr3;
		break;
	case UCR4:
		return sport->ucr4;
		break;
	case UFCR:
		return sport->ufcr;
		break;
	default:
		return readl(sport->port.membase + offset);
	}
}