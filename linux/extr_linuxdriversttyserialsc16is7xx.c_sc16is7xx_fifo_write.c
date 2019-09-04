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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {int /*<<< orphan*/  regmap; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int const SC16IS7XX_REG_SHIFT ; 
 int const SC16IS7XX_THR_REG ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_raw_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int sc16is7xx_line (struct uart_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sc16is7xx_fifo_write(struct uart_port *port, u8 to_send)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	const u8 line = sc16is7xx_line(port);
	u8 addr = (SC16IS7XX_THR_REG << SC16IS7XX_REG_SHIFT) | line;

	/*
	 * Don't send zero-length data, at least on SPI it confuses the chip
	 * delivering wrong TXLVL data.
	 */
	if (unlikely(!to_send))
		return;

	regcache_cache_bypass(s->regmap, true);
	regmap_raw_write(s->regmap, addr, s->buf, to_send);
	regcache_cache_bypass(s->regmap, false);
}