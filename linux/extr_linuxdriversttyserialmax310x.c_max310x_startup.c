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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct max310x_port {TYPE_1__* devtype; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power ) (struct uart_port*,int) ;} ;

/* Variables and functions */
 unsigned int MAX310X_FLOWLVL_HALT (int) ; 
 int /*<<< orphan*/  MAX310X_FLOWLVL_REG ; 
 unsigned int MAX310X_FLOWLVL_RES (int) ; 
 int /*<<< orphan*/  MAX310X_IRQEN_REG ; 
 int /*<<< orphan*/  MAX310X_IRQSTS_REG ; 
 unsigned int MAX310X_IRQ_CTS_BIT ; 
 unsigned int MAX310X_IRQ_RXEMPTY_BIT ; 
 unsigned int MAX310X_IRQ_TXEMPTY_BIT ; 
 int /*<<< orphan*/  MAX310X_MODE1_REG ; 
 unsigned int MAX310X_MODE1_TRNSCVCTRL_BIT ; 
 unsigned int MAX310X_MODE2_FIFORST_BIT ; 
 int /*<<< orphan*/  MAX310X_MODE2_REG ; 
 unsigned int MAX310X_MODE2_RXEMPTINV_BIT ; 
 struct max310x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max310x_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max310x_port_update (struct uart_port*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max310x_port_write (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int) ; 

__attribute__((used)) static int max310x_startup(struct uart_port *port)
{
	struct max310x_port *s = dev_get_drvdata(port->dev);
	unsigned int val;

	s->devtype->power(port, 1);

	/* Configure MODE1 register */
	max310x_port_update(port, MAX310X_MODE1_REG,
			    MAX310X_MODE1_TRNSCVCTRL_BIT, 0);

	/* Configure MODE2 register & Reset FIFOs*/
	val = MAX310X_MODE2_RXEMPTINV_BIT | MAX310X_MODE2_FIFORST_BIT;
	max310x_port_write(port, MAX310X_MODE2_REG, val);
	max310x_port_update(port, MAX310X_MODE2_REG,
			    MAX310X_MODE2_FIFORST_BIT, 0);

	/* Configure flow control levels */
	/* Flow control halt level 96, resume level 48 */
	max310x_port_write(port, MAX310X_FLOWLVL_REG,
			   MAX310X_FLOWLVL_RES(48) | MAX310X_FLOWLVL_HALT(96));

	/* Clear IRQ status register */
	max310x_port_read(port, MAX310X_IRQSTS_REG);

	/* Enable RX, TX, CTS change interrupts */
	val = MAX310X_IRQ_RXEMPTY_BIT | MAX310X_IRQ_TXEMPTY_BIT;
	max310x_port_write(port, MAX310X_IRQEN_REG, val | MAX310X_IRQ_CTS_BIT);

	return 0;
}