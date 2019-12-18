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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  bloom_t ;

/* Variables and functions */
 int add_or_check (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bloom_filter_check(lua_State *L) {
  bloom_t *filter = (bloom_t *)luaL_checkudata(L, 1, "bloom.filter");
  size_t length;
  const uint8 *buffer = (uint8 *) luaL_checklstring(L, 2, &length);

  bool rc = add_or_check(buffer, length, filter, false);

  lua_pushboolean(L, rc);
  return 1;
}