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
 int IN_RODATA_AREA (char const*) ; 

__attribute__((used)) static int lua_is_ptr_in_ro_area(const char *p) {
#ifdef LUA_CROSS_COMPILER
  return 0;         // TStrings are never in RO in luac.cross
#else
  return IN_RODATA_AREA(p);
#endif
}