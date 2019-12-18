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
 int* bytes64 ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypto_base64_encode( lua_State* L )
{
  int len, i;
  const char* msg = luaL_checklstring(L, 1, &len);
  luaL_Buffer out;

  luaL_buffinit(L, &out);
  for (i = 0; i < len; i += 3) {
    int a = msg[i];
    int b = (i + 1 < len) ? msg[i + 1] : 0;
    int c = (i + 2 < len) ? msg[i + 2] : 0;
    luaL_addchar(&out, bytes64[a >> 2]);
    luaL_addchar(&out, bytes64[((a & 3) << 4) | (b >> 4)]);
    luaL_addchar(&out, (i + 1 < len) ? bytes64[((b & 15) << 2) | (c >> 6)] : 61);
    luaL_addchar(&out, (i + 2 < len) ? bytes64[(c & 63)] : 61);
  }
  luaL_pushresult(&out);
  return 1;
}