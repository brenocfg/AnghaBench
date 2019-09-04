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
struct device_driver {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int pcistub_device_id_remove (int,int,int,int) ; 
 int str_to_slot (char const*,int*,int*,int*,int*) ; 

__attribute__((used)) static ssize_t remove_slot_store(struct device_driver *drv, const char *buf,
				 size_t count)
{
	int domain, bus, slot, func;
	int err;

	err = str_to_slot(buf, &domain, &bus, &slot, &func);
	if (err)
		goto out;

	err = pcistub_device_id_remove(domain, bus, slot, func);

out:
	if (!err)
		err = count;
	return err;
}