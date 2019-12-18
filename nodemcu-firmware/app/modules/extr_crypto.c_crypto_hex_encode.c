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
 int /*<<< orphan*/ * crypto_hexbytes ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypto_hex_encode( lua_State* L)
{
  int len, i;
  const char* msg = luaL_checklstring(L, 1, &len);
  luaL_Buffer out;

  luaL_buffinit(L, &out);
  for (i = 0; i < len; i++) {
    luaL_addchar(&out, crypto_hexbytes[msg[i] >> 4]);
    luaL_addchar(&out, crypto_hexbytes[msg[i] & 0xf]);
  }
  luaL_pushresult(&out);
  return 1;
}