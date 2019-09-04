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
struct hvc_iucv_private {int /*<<< orphan*/  srv_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBCASC (char*,size_t) ; 
 struct hvc_iucv_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t hvc_iucv_dev_termid_show(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct hvc_iucv_private *priv = dev_get_drvdata(dev);
	size_t len;

	len = sizeof(priv->srv_name);
	memcpy(buf, priv->srv_name, len);
	EBCASC(buf, len);
	buf[len++] = '\n';
	return len;
}