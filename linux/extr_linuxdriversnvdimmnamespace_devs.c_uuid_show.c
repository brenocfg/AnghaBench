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
typedef  int /*<<< orphan*/  u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * namespace_to_uuid (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t uuid_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	u8 *uuid = namespace_to_uuid(dev);

	if (IS_ERR(uuid))
		return PTR_ERR(uuid);
	if (uuid)
		return sprintf(buf, "%pUb\n", uuid);
	return sprintf(buf, "\n");
}