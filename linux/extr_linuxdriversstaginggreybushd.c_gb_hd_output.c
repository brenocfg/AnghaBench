#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_host_device {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* output ) (struct gb_host_device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct gb_host_device*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int gb_hd_output(struct gb_host_device *hd, void *req, u16 size, u8 cmd,
		 bool async)
{
	if (!hd || !hd->driver || !hd->driver->output)
		return -EINVAL;
	return hd->driver->output(hd, req, size, cmd, async);
}