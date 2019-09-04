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
typedef  int /*<<< orphan*/  u8 ;
struct aspeed_vuart {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ ASPEED_VUART_GCRA ; 
 int /*<<< orphan*/  ASPEED_VUART_GCRA_VUART_EN ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void aspeed_vuart_set_enabled(struct aspeed_vuart *vuart, bool enabled)
{
	u8 reg = readb(vuart->regs + ASPEED_VUART_GCRA);

	if (enabled)
		reg |= ASPEED_VUART_GCRA_VUART_EN;
	else
		reg &= ~ASPEED_VUART_GCRA_VUART_EN;

	writeb(reg, vuart->regs + ASPEED_VUART_GCRA);
}