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
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int of_device_get_modalias (struct device*,char*,int) ; 
 int request_module (char*) ; 

int of_device_request_module(struct device *dev)
{
	char *str;
	ssize_t size;
	int ret;

	size = of_device_get_modalias(dev, NULL, 0);
	if (size < 0)
		return size;

	str = kmalloc(size + 1, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	of_device_get_modalias(dev, str, size);
	str[size] = '\0';
	ret = request_module(str);
	kfree(str);

	return ret;
}