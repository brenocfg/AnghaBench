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
typedef  scalar_t__ u32 ;
struct qcom_geni_serial_port {scalar_t__ loopback; } ;
struct platform_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ MAX_LOOPBACK_CFG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct qcom_geni_serial_port* platform_get_drvdata (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t loopback_store(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t size)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct qcom_geni_serial_port *port = platform_get_drvdata(pdev);
	u32 loopback;

	if (kstrtoint(buf, 0, &loopback) || loopback > MAX_LOOPBACK_CFG) {
		dev_err(dev, "Invalid input\n");
		return -EINVAL;
	}
	port->loopback = loopback;
	return size;
}