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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypto_mask( lua_State* L )
{
  int len, mask_len, i;
  const char* msg = luaL_checklstring(L, 1, &len);
  const char* mask = luaL_checklstring(L, 2, &mask_len);
  luaL_Buffer b;

  if(mask_len <= 0)
    return luaL_error(L, "invalid argument: mask");

  luaL_buffinit(L, &b);
  for (i = 0; i < len; i++) {
    luaL_addchar(&b, msg[i] ^ mask[i % mask_len]);
  }

  luaL_pushresult(&b);
  return 1;
}