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
typedef  scalar_t__ lua_Number ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int Uinttype ;
typedef  scalar_t__ Inttype ;

/* Variables and functions */
 int LITTLE ; 
 int MAXINTSIZE ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void putinteger (lua_State *L, luaL_Buffer *b, int arg, int endian,
                        int size) {
  lua_Number n = luaL_checknumber(L, arg);
  Uinttype value;
  char buff[MAXINTSIZE];
  if (n < 0)
    value = (Uinttype)(Inttype)n;
  else
    value = (Uinttype)n;
  if (endian == LITTLE) {
    int i;
    for (i = 0; i < size; i++) {
      buff[i] = (value & 0xff);
      value >>= 8;
    }
  }
  else {
    int i;
    for (i = size - 1; i >= 0; i--) {
      buff[i] = (value & 0xff);
      value >>= 8;
    }
  }
  luaL_addlstring(b, buff, size);
}