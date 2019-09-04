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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
#define  LUA_TNIL 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int /*<<< orphan*/  cast_num (int) ; 
 int /*<<< orphan*/  const* luaH_getnum_ro (void*,int) ; 
 int /*<<< orphan*/  const* luaH_getstr_ro (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* luaO_nilobject ; 
 int /*<<< orphan*/  lua_number2int (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luai_numeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rawtsvalue (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 

const TValue *luaH_get_ro (void *t, const TValue *key) {
  switch (ttype(key)) {
    case LUA_TNIL: return luaO_nilobject;
    case LUA_TSTRING: return luaH_getstr_ro(t, rawtsvalue(key));
    case LUA_TNUMBER: {
      int k;
      lua_Number n = nvalue(key);
      lua_number2int(k, n);
      if (luai_numeq(cast_num(k), nvalue(key))) /* index is int? */
        return luaH_getnum_ro(t, k);  /* use specialized version */
      /* else go through */
    }
    default: {
      return luaO_nilobject;
    }
  }
}