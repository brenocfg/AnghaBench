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
struct gb_i2c_device {int dummy; } ;

/* Variables and functions */
 int gb_i2c_functionality_operation (struct gb_i2c_device*) ; 

__attribute__((used)) static int gb_i2c_device_setup(struct gb_i2c_device *gb_i2c_dev)
{
	/* Assume the functionality never changes, just get it once */
	return gb_i2c_functionality_operation(gb_i2c_dev);
}