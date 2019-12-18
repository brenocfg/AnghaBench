#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_25__ ;
typedef  struct TYPE_31__   TYPE_23__ ;
typedef  struct TYPE_30__   TYPE_21__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_19__ ;
typedef  struct TYPE_27__   TYPE_17__ ;

/* Type definitions */
struct TYPE_34__ {TYPE_5__* gray; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_29__ {int /*<<< orphan*/  value; } ;
struct TYPE_35__ {TYPE_1__ u; int /*<<< orphan*/ * v; } ;
typedef  TYPE_4__ UpVal ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_36__ {int /*<<< orphan*/  gch; } ;
struct TYPE_33__ {TYPE_5__* gclist; } ;
struct TYPE_32__ {TYPE_2__ c; } ;
struct TYPE_31__ {TYPE_5__* gclist; } ;
struct TYPE_30__ {TYPE_5__* gclist; } ;
struct TYPE_28__ {TYPE_5__* gclist; } ;
struct TYPE_27__ {int /*<<< orphan*/ * env; int /*<<< orphan*/ * metatable; } ;
typedef  TYPE_5__ GCObject ;

/* Variables and functions */
#define  LUA_TFUNCTION 134 
#define  LUA_TPROTO 133 
#define  LUA_TSTRING 132 
#define  LUA_TTABLE 131 
#define  LUA_TTHREAD 130 
#define  LUA_TUPVAL 129 
#define  LUA_TUSERDATA 128 
 TYPE_25__* gco2cl (TYPE_5__*) ; 
 TYPE_23__* gco2h (TYPE_5__*) ; 
 TYPE_21__* gco2p (TYPE_5__*) ; 
 TYPE_19__* gco2th (TYPE_5__*) ; 
 TYPE_17__* gco2u (TYPE_5__*) ; 
 TYPE_4__* gco2uv (TYPE_5__*) ; 
 int gettt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gray2black (TYPE_5__*) ; 
 scalar_t__ isLFSobject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdead (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ iswhite (TYPE_5__*) ; 
 int /*<<< orphan*/  luaR_isrotable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markobject (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markvalue (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  white2gray (TYPE_5__*) ; 

__attribute__((used)) static void reallymarkobject (global_State *g, GCObject *o) {
  /* don't mark LFS Protos (or strings) */
  if (gettt(&o->gch) == LUA_TPROTO && isLFSobject(&(o->gch)))
    return;

  lua_assert(iswhite(o) && !isdead(g, o));
  white2gray(o);
  switch (gettt(&o->gch)) {
    case LUA_TSTRING: {
      return;
    }
    case LUA_TUSERDATA: {
      Table *mt = gco2u(o)->metatable;
      gray2black(o);  /* udata are never gray */
      if (mt && !luaR_isrotable(mt)) markobject(g, mt);
      markobject(g, gco2u(o)->env);
      return;
    }
    case LUA_TUPVAL: {
      UpVal *uv = gco2uv(o);
      markvalue(g, uv->v);
      if (uv->v == &uv->u.value)  /* closed? */
        gray2black(o);  /* open upvalues are never black */
      return;
    }
    case LUA_TFUNCTION: {
      gco2cl(o)->c.gclist = g->gray;
      g->gray = o;
      break;
    }
    case LUA_TTABLE: {
      gco2h(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    case LUA_TTHREAD: {
      gco2th(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    case LUA_TPROTO: {
      gco2p(o)->gclist = g->gray;
      g->gray = o;
      break;
    }
    default: lua_assert(0);
  }
}