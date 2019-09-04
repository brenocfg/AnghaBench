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
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct usbip_host_driver*) ;} ;
struct usbip_host_driver {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usbip_host_driver*) ; 

__attribute__((used)) static inline void usbip_driver_close(struct usbip_host_driver *hdriver)
{
	if (!hdriver->ops.close)
		return;
	hdriver->ops.close(hdriver);
}