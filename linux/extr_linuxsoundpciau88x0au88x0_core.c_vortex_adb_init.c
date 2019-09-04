#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mmio; } ;
typedef  TYPE_1__ vortex_t ;

/* Variables and functions */
 int ROUTE_MASK ; 
 scalar_t__ VORTEX_ADB_CHNBASE ; 
 int VORTEX_ADB_CHNBASE_COUNT ; 
 scalar_t__ VORTEX_ADB_RTBASE ; 
 int VORTEX_ADB_RTBASE_COUNT ; 
 scalar_t__ VORTEX_ADB_SR ; 
 int hwread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void vortex_adb_init(vortex_t * vortex)
{
	int i;
	/* it looks like we are writing more than we need to...
	 * if we write what we are supposed to it breaks things... */
	hwwrite(vortex->mmio, VORTEX_ADB_SR, 0);
	for (i = 0; i < VORTEX_ADB_RTBASE_COUNT; i++)
		hwwrite(vortex->mmio, VORTEX_ADB_RTBASE + (i << 2),
			hwread(vortex->mmio,
			       VORTEX_ADB_RTBASE + (i << 2)) | ROUTE_MASK);
	for (i = 0; i < VORTEX_ADB_CHNBASE_COUNT; i++) {
		hwwrite(vortex->mmio, VORTEX_ADB_CHNBASE + (i << 2),
			hwread(vortex->mmio,
			       VORTEX_ADB_CHNBASE + (i << 2)) | ROUTE_MASK);
	}
}