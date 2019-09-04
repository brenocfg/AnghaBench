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
struct usb3503 {int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb3503* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct usb3503*) ; 
 int usb3503_probe (struct usb3503*) ; 

__attribute__((used)) static int usb3503_platform_probe(struct platform_device *pdev)
{
	struct usb3503 *hub;

	hub = devm_kzalloc(&pdev->dev, sizeof(struct usb3503), GFP_KERNEL);
	if (!hub)
		return -ENOMEM;
	hub->dev = &pdev->dev;
	platform_set_drvdata(pdev, hub);

	return usb3503_probe(hub);
}