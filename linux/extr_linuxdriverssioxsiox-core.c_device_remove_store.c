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
struct siox_master {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  siox_device_remove (struct siox_master*) ; 
 struct siox_master* to_siox_master (struct device*) ; 

__attribute__((used)) static ssize_t device_remove_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct siox_master *smaster = to_siox_master(dev);

	/* XXX? require to write <type> <inbytes> <outbytes> */
	siox_device_remove(smaster);

	return count;
}