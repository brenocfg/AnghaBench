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
struct usb_hcd {int dummy; } ;
struct sl811 {int /*<<< orphan*/  addr_reg; int /*<<< orphan*/  data_reg; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct sl811* hcd_to_sl811 (struct usb_hcd*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_debug_file (struct sl811*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int
sl811h_remove(struct platform_device *dev)
{
	struct usb_hcd		*hcd = platform_get_drvdata(dev);
	struct sl811		*sl811 = hcd_to_sl811(hcd);
	struct resource		*res;

	remove_debug_file(sl811);
	usb_remove_hcd(hcd);

	/* some platforms may use IORESOURCE_IO */
	res = platform_get_resource(dev, IORESOURCE_MEM, 1);
	if (res)
		iounmap(sl811->data_reg);

	res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (res)
		iounmap(sl811->addr_reg);

	usb_put_hcd(hcd);
	return 0;
}