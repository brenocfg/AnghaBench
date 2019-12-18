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

/* Variables and functions */
 int /*<<< orphan*/  frontend_save_callback ; 
 int /*<<< orphan*/  obs_frontend_add_save_callback (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void add_save_callback_defer(void *cb)
{
	obs_frontend_add_save_callback(frontend_save_callback, cb);
}