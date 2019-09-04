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
typedef  int uint8_t ;
struct uart_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irda_speed_t ;
typedef  int irda_module_t ;

/* Variables and functions */
#define  HP_IRDA 130 
 int /*<<< orphan*/  IRDA_TX_4MBPS ; 
 int IRMSEL ; 
 int IRMSEL_HP ; 
 int IRMSEL_SHARP ; 
 int IRMSEL_TEMIC ; 
#define  SHARP_IRDA 129 
 int /*<<< orphan*/  SIUIRSEL ; 
#define  TEMIC_IRDA 128 
 int TMICMODE ; 
 int TMICTX ; 
 int siu_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct uart_port* siu_uart_ports ; 
 int /*<<< orphan*/  siu_write (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vr41xx_select_irda_module(irda_module_t module, irda_speed_t speed)
{
	struct uart_port *port;
	unsigned long flags;
	uint8_t irsel;

	port = &siu_uart_ports[0];

	spin_lock_irqsave(&port->lock, flags);

	irsel = siu_read(port, SIUIRSEL);
	irsel &= ~(IRMSEL | TMICTX | TMICMODE);
	switch (module) {
	case SHARP_IRDA:
		irsel |= IRMSEL_SHARP;
		break;
	case TEMIC_IRDA:
		irsel |= IRMSEL_TEMIC | TMICMODE;
		if (speed == IRDA_TX_4MBPS)
			irsel |= TMICTX;
		break;
	case HP_IRDA:
		irsel |= IRMSEL_HP;
		break;
	default:
		break;
	}
	siu_write(port, SIUIRSEL, irsel);

	spin_unlock_irqrestore(&port->lock, flags);
}