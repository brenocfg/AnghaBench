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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int ALIGN (size_t) ; 
 scalar_t__ LUA_MAX_FLASH_SIZE ; 
 int WORDSHIFT ; 
 scalar_t__ curOffset ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ flashImage ; 

__attribute__((used)) static void *flashAlloc(lua_State* L, size_t n) {
  void *p = (void *)(flashImage + curOffset);
  curOffset += ALIGN(n)>>WORDSHIFT;
  if (curOffset > LUA_MAX_FLASH_SIZE) {
    fatal("Out of Flash memory");
  }
  return p;
}