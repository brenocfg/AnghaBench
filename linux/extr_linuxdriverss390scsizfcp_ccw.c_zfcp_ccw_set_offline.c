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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int zfcp_ccw_offline_sync (struct ccw_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int zfcp_ccw_set_offline(struct ccw_device *cdev)
{
	return zfcp_ccw_offline_sync(cdev, 0, "ccsoff1");
}