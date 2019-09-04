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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int /*<<< orphan*/  IOP_HWSOFT_RESET ; 
 int aac_reset_adapter (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t aac_store_reset_adapter(struct device *device,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	int retval = -EACCES;

	if (!capable(CAP_SYS_ADMIN))
		return retval;

	retval = aac_reset_adapter(shost_priv(class_to_shost(device)),
					buf[0] == '!', IOP_HWSOFT_RESET);
	if (retval >= 0)
		retval = count;

	return retval;
}