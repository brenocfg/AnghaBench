#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_22__ {scalar_t__ sizeupvalues; } ;
struct TYPE_21__ {scalar_t__ nupvalues; TYPE_7__* p; } ;
struct TYPE_20__ {char const* name; int /*<<< orphan*/ * Z; TYPE_1__* L; } ;
typedef  TYPE_2__ LoadState ;
typedef  TYPE_3__ LClosure ;

/* Variables and functions */
 char const* LUA_SIGNATURE ; 
 int /*<<< orphan*/  LoadByte (TYPE_2__*) ; 
 int /*<<< orphan*/  LoadFunction (TYPE_2__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buff ; 
 int /*<<< orphan*/  checkHeader (TYPE_2__*) ; 
 int /*<<< orphan*/  luaD_inctop (TYPE_1__*) ; 
 TYPE_3__* luaF_newLclosure (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* luaF_newproto (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  luai_verifycode (TYPE_1__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  setclLvalue (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

LClosure *luaU_undump(lua_State *L, ZIO *Z, const char *name) {
  LoadState S;
  LClosure *cl;
  if (*name == '@' || *name == '=')
    S.name = name + 1;
  else if (*name == LUA_SIGNATURE[0])
    S.name = "binary string";
  else
    S.name = name;
  S.L = L;
  S.Z = Z;
  checkHeader(&S);
  cl = luaF_newLclosure(L, LoadByte(&S));
  setclLvalue(L, L->top, cl);
  luaD_inctop(L);
  cl->p = luaF_newproto(L);
  LoadFunction(&S, cl->p, NULL);
  lua_assert(cl->nupvalues == cl->p->sizeupvalues);
  luai_verifycode(L, buff, cl->p);
  return cl;
}