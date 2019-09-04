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
 char* crypto_hexbytes ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int crypto_hex_encode( lua_State* L)
{
  int len;
  const char* msg = luaL_checklstring(L, 1, &len);
  char* out = (char*)c_malloc(len * 2);
  int i, j = 0;
  for (i = 0; i < len; i++) {
    out[j++] = crypto_hexbytes[msg[i] >> 4];
    out[j++] = crypto_hexbytes[msg[i] & 0xf];
  }
  lua_pushlstring(L, out, len*2);
  c_free(out);
  return 1;
}