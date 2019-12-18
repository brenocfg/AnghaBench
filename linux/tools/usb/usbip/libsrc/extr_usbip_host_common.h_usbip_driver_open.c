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
struct TYPE_2__ {int (* open ) (struct usbip_host_driver*) ;} ;
struct usbip_host_driver {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct usbip_host_driver*) ; 

__attribute__((used)) static inline int usbip_driver_open(struct usbip_host_driver *hdriver)
{
	if (!hdriver->ops.open)
		return -EOPNOTSUPP;
	return hdriver->ops.open(hdriver);
}