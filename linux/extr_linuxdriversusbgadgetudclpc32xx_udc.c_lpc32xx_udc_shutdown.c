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
struct platform_device {int dummy; } ;
struct lpc32xx_udc {int dummy; } ;

/* Variables and functions */
 struct lpc32xx_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pullup (struct lpc32xx_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lpc32xx_udc_shutdown(struct platform_device *dev)
{
	/* Force disconnect on reboot */
	struct lpc32xx_udc *udc = platform_get_drvdata(dev);

	pullup(udc, 0);
}