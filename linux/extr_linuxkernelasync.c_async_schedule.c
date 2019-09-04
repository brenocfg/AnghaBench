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
typedef  int /*<<< orphan*/  async_func_t ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  __async_schedule (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  async_dfl_domain ; 

async_cookie_t async_schedule(async_func_t func, void *data)
{
	return __async_schedule(func, data, &async_dfl_domain);
}