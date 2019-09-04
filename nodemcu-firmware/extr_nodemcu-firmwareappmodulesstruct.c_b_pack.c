#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_5__ {int /*<<< orphan*/  endian; } ;
typedef  TYPE_1__ Header ;

/* Variables and functions */
 int /*<<< orphan*/  controloptions (int /*<<< orphan*/ *,int,char const**,TYPE_1__*) ; 
 int /*<<< orphan*/  correctbytes (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defaultoptions (TYPE_1__*) ; 
 int gettoalign (size_t,TYPE_1__*,int,size_t) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 double luaL_checknumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 size_t optsize (int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  putinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int b_pack (lua_State *L) {
  luaL_Buffer b;
  const char *fmt = luaL_checkstring(L, 1);
  Header h;
  int arg = 2;
  size_t totalsize = 0;
  defaultoptions(&h);
  lua_pushnil(L);  /* mark to separate arguments from string buffer */
  luaL_buffinit(L, &b);
  while (*fmt != '\0') {
    int opt = *fmt++;
    size_t size = optsize(L, opt, &fmt);
    int toalign = gettoalign(totalsize, &h, opt, size);
    totalsize += toalign;
    while (toalign-- > 0) luaL_addchar(&b, '\0');
    switch (opt) {
      case 'b': case 'B': case 'h': case 'H':
      case 'l': case 'L': case 'T': case 'i': case 'I': {  /* integer types */
        putinteger(L, &b, arg++, h.endian, size);
        break;
      }
      case 'x': {
        luaL_addchar(&b, '\0');
        break;
      }
#ifndef LUA_NUMBER_INTEGRAL
      case 'f': {
        float f = (float)luaL_checknumber(L, arg++);
        correctbytes((char *)&f, size, h.endian);
        luaL_addlstring(&b, (char *)&f, size);
        break;
      }
      case 'd': {
        double d = luaL_checknumber(L, arg++);
        correctbytes((char *)&d, size, h.endian);
        luaL_addlstring(&b, (char *)&d, size);
        break;
      }
#endif
      case 'c': case 's': {
        size_t l;
        const char *s = luaL_checklstring(L, arg++, &l);
        if (size == 0) size = l;
        luaL_argcheck(L, l >= (size_t)size, arg, "string too short");
        luaL_addlstring(&b, s, size);
        if (opt == 's') {
          luaL_addchar(&b, '\0');  /* add zero at the end */
          size++;
        }
        break;
      }
      default: controloptions(L, opt, &fmt, &h);
    }
    totalsize += size;
  }
  luaL_pushresult(&b);
  return 1;
}