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
 int /*<<< orphan*/  c_free (char*) ; 
 scalar_t__ c_malloc (int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int crypto_mask( lua_State* L )
{
  int len, mask_len;
  const char* msg = luaL_checklstring(L, 1, &len);
  const char* mask = luaL_checklstring(L, 2, &mask_len);

  if(mask_len <= 0)
    return luaL_error(L, "invalid argument: mask");

  int i;
  char* copy = (char*)c_malloc(len);

  for (i = 0; i < len; i++) {
    copy[i] = msg[i] ^ mask[i % mask_len];
  }
  lua_pushlstring(L, copy, len);
  c_free(copy);

  return 1;
}