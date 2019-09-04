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
struct olpc_ec_driver {int dummy; } ;

/* Variables and functions */
 void* ec_cb_arg ; 
 struct olpc_ec_driver* ec_driver ; 

void olpc_ec_driver_register(struct olpc_ec_driver *drv, void *arg)
{
	ec_driver = drv;
	ec_cb_arg = arg;
}