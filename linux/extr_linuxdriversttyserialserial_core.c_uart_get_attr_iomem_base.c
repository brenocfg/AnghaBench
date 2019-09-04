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
struct tty_port {int dummy; } ;
struct serial_struct {scalar_t__ iomem_base; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct tty_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  uart_get_info (struct tty_port*,struct serial_struct*) ; 

__attribute__((used)) static ssize_t uart_get_attr_iomem_base(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct serial_struct tmp;
	struct tty_port *port = dev_get_drvdata(dev);

	uart_get_info(port, &tmp);
	return snprintf(buf, PAGE_SIZE, "0x%lX\n", (unsigned long)tmp.iomem_base);
}