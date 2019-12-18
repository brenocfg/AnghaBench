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
 int /*<<< orphan*/  async_dfl_domain ; 
 int /*<<< orphan*/  async_schedule_node_domain (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 

async_cookie_t async_schedule_node(async_func_t func, void *data, int node)
{
	return async_schedule_node_domain(func, data, node, &async_dfl_domain);
}