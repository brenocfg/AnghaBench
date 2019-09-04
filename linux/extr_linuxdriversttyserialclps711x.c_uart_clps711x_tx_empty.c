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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  dev; } ;
struct clps711x_port {int /*<<< orphan*/  syscon; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSFLG_OFFSET ; 
 int SYSFLG_UBUSY ; 
 unsigned int TIOCSER_TEMT ; 
 struct clps711x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int uart_clps711x_tx_empty(struct uart_port *port)
{
	struct clps711x_port *s = dev_get_drvdata(port->dev);
	u32 sysflg = 0;

	regmap_read(s->syscon, SYSFLG_OFFSET, &sysflg);

	return (sysflg & SYSFLG_UBUSY) ? 0 : TIOCSER_TEMT;
}