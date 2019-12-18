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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void push_hex_string(lua_State *L, const uint8 *buf, int len, char *sep) {
  luaL_Buffer b;
  luaL_buffinit(L, &b);

  int i;
  for (i = 0; i < len; i++) {
    if (i && sep && *sep) {
      luaL_addstring(&b, sep);
    }
    char hex[3];

    uint8 c = buf[i];

    hex[0] = "0123456789abcdef"[c >> 4];
    hex[1] = "0123456789abcdef"[c & 0xf];
    hex[2] = 0;
    luaL_addstring(&b, hex);
  }

  luaL_pushresult(&b);
}