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
 int /*<<< orphan*/  enduser_setup_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getstate () ; 

__attribute__((used)) static void enduser_setup_stop_callback(void *ptr)
{
  enduser_setup_stop(lua_getstate());
}