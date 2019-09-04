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
typedef  int uint32_t ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int kstrtou32 (char const*,int,int*) ; 
 int /*<<< orphan*/  pisnd_spi_flash_leds (int) ; 

__attribute__((used)) static ssize_t pisnd_led_store(
	struct kobject *kobj,
	struct kobj_attribute *attr,
	const char *buf,
	size_t length
	)
{
	uint32_t timeout;
	int err;

	err = kstrtou32(buf, 10, &timeout);

	if (err == 0 && timeout <= 255)
		pisnd_spi_flash_leds(timeout);

	return length;
}