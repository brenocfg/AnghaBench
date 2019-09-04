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
 int /*<<< orphan*/  DCON_REG_SCAN_INT ; 
 int /*<<< orphan*/  dcon_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int kstrtou16 (char const*,int,unsigned short*) ; 
 unsigned short resumeline ; 

__attribute__((used)) static ssize_t dcon_resumeline_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	unsigned short rl;
	int rc;

	rc = kstrtou16(buf, 10, &rl);
	if (rc)
		return rc;

	resumeline = rl;
	dcon_write(dev_get_drvdata(dev), DCON_REG_SCAN_INT, resumeline);

	return count;
}