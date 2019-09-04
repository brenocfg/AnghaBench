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
struct usb3503 {scalar_t__ clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct usb3503* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int usb3503_platform_remove(struct platform_device *pdev)
{
	struct usb3503 *hub;

	hub = platform_get_drvdata(pdev);
	if (hub->clk)
		clk_disable_unprepare(hub->clk);

	return 0;
}