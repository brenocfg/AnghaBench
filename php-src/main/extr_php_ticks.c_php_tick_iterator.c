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
struct st_tick_function {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_tick_iterator(void *d, void *arg)
{
	struct st_tick_function *data = (struct st_tick_function *)d;
	data->func(*((int *)arg), data->arg);
}