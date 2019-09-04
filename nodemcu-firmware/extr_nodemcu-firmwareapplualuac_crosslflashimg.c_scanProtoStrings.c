#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int sizek; int sizeupvalues; int sizelocvars; int sizep; struct TYPE_5__** p; TYPE_1__* locvars; scalar_t__* upvalues; scalar_t__ k; scalar_t__ source; } ;
struct TYPE_4__ {scalar_t__ varname; } ;
typedef  TYPE_2__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  addTS (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rawtsvalue (scalar_t__) ; 
 scalar_t__ ttisstring (scalar_t__) ; 

__attribute__((used)) static void scanProtoStrings(lua_State *L, const Proto* f) {
  /* Table at L->Top[-1] is used to collect the strings */
  int i;

  if (f->source)
    addTS(L, f->source);

#ifdef LUA_OPTIMIZE_DEBUG
  if (f->packedlineinfo)
    addTS(L, luaS_new(L, cast(const char *, f->packedlineinfo)));
#endif

  for (i = 0; i < f->sizek; i++) {
    if (ttisstring(f->k + i))
      addTS(L, rawtsvalue(f->k + i));
  }
  for (i = 0; i < f->sizeupvalues; i++) addTS(L, f->upvalues[i]);
  for (i = 0; i < f->sizelocvars; i++)  addTS(L, f->locvars[i].varname);
  for (i = 0; i < f->sizep; i++)        scanProtoStrings(L, f->p[i]);
}