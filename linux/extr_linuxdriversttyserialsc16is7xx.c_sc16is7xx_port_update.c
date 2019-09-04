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
typedef  int const u8 ;
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int const SC16IS7XX_REG_SHIFT ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int const,int const,int const) ; 
 int sc16is7xx_line (struct uart_port*) ; 

__attribute__((used)) static void sc16is7xx_port_update(struct uart_port *port, u8 reg,
				  u8 mask, u8 val)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	const u8 line = sc16is7xx_line(port);

	regmap_update_bits(s->regmap, (reg << SC16IS7XX_REG_SHIFT) | line,
			   mask, val);
}