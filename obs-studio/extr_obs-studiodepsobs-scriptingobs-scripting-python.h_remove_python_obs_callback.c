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
struct python_obs_callback {int /*<<< orphan*/ * func; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_script_callback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void remove_python_obs_callback(struct python_obs_callback *cb)
{
	remove_script_callback(&cb->base);

	Py_XDECREF(cb->func);
	cb->func = NULL;
}