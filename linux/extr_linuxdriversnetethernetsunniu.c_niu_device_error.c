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
typedef  scalar_t__ u64 ;
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SYS_ERR_STAT ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  niu_log_device_error (struct niu*,scalar_t__) ; 
 scalar_t__ nr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_device_error(struct niu *np)
{
	u64 stat = nr64(SYS_ERR_STAT);

	netdev_err(np->dev, "Core device error, stat[%llx]\n",
		   (unsigned long long)stat);

	niu_log_device_error(np, stat);

	return -ENODEV;
}