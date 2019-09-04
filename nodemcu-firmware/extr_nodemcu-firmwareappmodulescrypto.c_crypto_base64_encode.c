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
 int* bytes64 ; 
 int /*<<< orphan*/  c_free (char*) ; 
 scalar_t__ c_malloc (int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int crypto_base64_encode( lua_State* L )
{
  int len;
  const char* msg = luaL_checklstring(L, 1, &len);
  int blen = (len + 2) / 3 * 4;
  char* out = (char*)c_malloc(blen);
  int j = 0, i;
  for (i = 0; i < len; i += 3) {
    int a = msg[i];
    int b = (i + 1 < len) ? msg[i + 1] : 0;
    int c = (i + 2 < len) ? msg[i + 2] : 0;
    out[j++] = bytes64[a >> 2];
    out[j++] = bytes64[((a & 3) << 4) | (b >> 4)];
    out[j++] = (i + 1 < len) ? bytes64[((b & 15) << 2) | (c >> 6)] : 61;
    out[j++] = (i + 2 < len) ? bytes64[(c & 63)] : 61;
  }
  lua_pushlstring(L, out, j);
  c_free(out);
  return 1;
}