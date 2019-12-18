#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int lua_Unsigned ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ lua_Number ;
typedef  int lua_Integer ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_6__ {float f; double d; int /*<<< orphan*/  buff; scalar_t__ n; } ;
struct TYPE_5__ {int /*<<< orphan*/  islittle; } ;
typedef  int KOption ;
typedef  TYPE_1__ Header ;
typedef  TYPE_2__ Ftypes ;

/* Variables and functions */
#define  Kchar 136 
#define  Kfloat 135 
#define  Kint 134 
#define  Knop 133 
#define  Kpaddalign 132 
#define  Kpadding 131 
#define  Kstring 130 
#define  Kuint 129 
#define  Kzstr 128 
 char LUAL_PACKPADBYTE ; 
 int NB ; 
 int SZINT ; 
 int /*<<< orphan*/  copywithendian (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int getdetails (TYPE_1__*,size_t,char const**,int*,int*) ; 
 int /*<<< orphan*/  initheader (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* luaL_prepbuffsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packint (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int str_pack (lua_State *L) {
  luaL_Buffer b;
  Header h;
  const char *fmt = luaL_checkstring(L, 1);  /* format string */
  int arg = 1;  /* current argument to pack */
  size_t totalsize = 0;  /* accumulate total size of result */
  initheader(L, &h);
  lua_pushnil(L);  /* mark to separate arguments from string buffer */
  luaL_buffinit(L, &b);
  while (*fmt != '\0') {
    int size, ntoalign;
    KOption opt = getdetails(&h, totalsize, &fmt, &size, &ntoalign);
    totalsize += ntoalign + size;
    while (ntoalign-- > 0)
     luaL_addchar(&b, LUAL_PACKPADBYTE);  /* fill alignment */
    arg++;
    switch (opt) {
      case Kint: {  /* signed integers */
        lua_Integer n = luaL_checkinteger(L, arg);
        if (size < SZINT) {  /* need overflow check? */
          lua_Integer lim = (lua_Integer)1 << ((size * NB) - 1);
          luaL_argcheck(L, -lim <= n && n < lim, arg, "integer overflow");
        }
        packint(&b, (lua_Unsigned)n, h.islittle, size, (n < 0));
        break;
      }
      case Kuint: {  /* unsigned integers */
        lua_Integer n = luaL_checkinteger(L, arg);
        if (size < SZINT)  /* need overflow check? */
          luaL_argcheck(L, (lua_Unsigned)n < ((lua_Unsigned)1 << (size * NB)),
                           arg, "unsigned overflow");
        packint(&b, (lua_Unsigned)n, h.islittle, size, 0);
        break;
      }
      case Kfloat: {  /* floating-point options */
        volatile Ftypes u;
        char *buff = luaL_prepbuffsize(&b, size);
        lua_Number n = luaL_checknumber(L, arg);  /* get argument */
        if (size == sizeof(u.f)) u.f = (float)n;  /* copy it into 'u' */
        else if (size == sizeof(u.d)) u.d = (double)n;
        else u.n = n;
        /* move 'u' to final result, correcting endianness if needed */
        copywithendian(buff, u.buff, size, h.islittle);
        luaL_addsize(&b, size);
        break;
      }
      case Kchar: {  /* fixed-size string */
        size_t len;
        const char *s = luaL_checklstring(L, arg, &len);
        luaL_argcheck(L, len <= (size_t)size, arg,
                         "string longer than given size");
        luaL_addlstring(&b, s, len);  /* add string */
        while (len++ < (size_t)size)  /* pad extra space */
          luaL_addchar(&b, LUAL_PACKPADBYTE);
        break;
      }
      case Kstring: {  /* strings with length count */
        size_t len;
        const char *s = luaL_checklstring(L, arg, &len);
        luaL_argcheck(L, size >= (int)sizeof(size_t) ||
                         len < ((size_t)1 << (size * NB)),
                         arg, "string length does not fit in given size");
        packint(&b, (lua_Unsigned)len, h.islittle, size, 0);  /* pack length */
        luaL_addlstring(&b, s, len);
        totalsize += len;
        break;
      }
      case Kzstr: {  /* zero-terminated string */
        size_t len;
        const char *s = luaL_checklstring(L, arg, &len);
        luaL_argcheck(L, strlen(s) == len, arg, "string contains zeros");
        luaL_addlstring(&b, s, len);
        luaL_addchar(&b, '\0');  /* add zero at the end */
        totalsize += len + 1;
        break;
      }
      case Kpadding: luaL_addchar(&b, LUAL_PACKPADBYTE);  /* FALLTHROUGH */
      case Kpaddalign: case Knop:
        arg--;  /* undo increment */
        break;
    }
  }
  luaL_pushresult(&b);
  return 1;
}