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
typedef  unsigned int u8 ;
struct uart_port {unsigned int iobase; int /*<<< orphan*/  dev; } ;
struct max310x_port {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 struct max310x_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static u8 max310x_port_read(struct uart_port *port, u8 reg)
{
	struct max310x_port *s = dev_get_drvdata(port->dev);
	unsigned int val = 0;

	regmap_read(s->regmap, port->iobase + reg, &val);

	return val;
}