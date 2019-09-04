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
struct vmlogrdr_priv_t {int autorecording; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct vmlogrdr_priv_t* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t vmlogrdr_autorecording_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct vmlogrdr_priv_t *priv = dev_get_drvdata(dev);
	ssize_t ret = count;

	switch (buf[0]) {
	case '0':
		priv->autorecording=0;
		break;
	case '1':
		priv->autorecording=1;
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}