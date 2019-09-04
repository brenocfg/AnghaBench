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
struct watchdog_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sp; } ;

/* Variables and functions */
 int rave_sp_exec (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_rave_sp_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int rave_sp_wdt_exec(struct watchdog_device *wdd, void *data,
			    size_t data_size)
{
	return rave_sp_exec(to_rave_sp_wdt(wdd)->sp,
			    data, data_size, NULL, 0);
}