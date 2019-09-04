#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_33__ {int stacksize; int size_ci; TYPE_7__* gclist; } ;
typedef  TYPE_3__ lua_State ;
typedef  int l_mem ;
struct TYPE_34__ {TYPE_7__* gray; TYPE_7__* grayagain; } ;
typedef  TYPE_4__ global_State ;
struct TYPE_35__ {int sizearray; TYPE_7__* gclist; } ;
typedef  TYPE_5__ Table ;
struct TYPE_32__ {int /*<<< orphan*/  nupvalues; } ;
struct TYPE_31__ {int /*<<< orphan*/  nupvalues; int /*<<< orphan*/  isC; TYPE_7__* gclist; } ;
struct TYPE_38__ {TYPE_2__ l; TYPE_1__ c; } ;
struct TYPE_37__ {int /*<<< orphan*/  gch; } ;
struct TYPE_36__ {int sizep; int sizek; int sizelocvars; int sizeupvalues; int sizecode; int sizelineinfo; TYPE_7__* gclist; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_6__ Proto ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  LocVar ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_7__ GCObject ;
typedef  TYPE_8__ Closure ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
#define  LUA_TFUNCTION 131 
#define  LUA_TPROTO 130 
#define  LUA_TTABLE 129 
#define  LUA_TTHREAD 128 
 int /*<<< orphan*/  black2gray (TYPE_7__*) ; 
 TYPE_8__* gco2cl (TYPE_7__*) ; 
 TYPE_5__* gco2h (TYPE_7__*) ; 
 TYPE_6__* gco2p (TYPE_7__*) ; 
 TYPE_3__* gco2th (TYPE_7__*) ; 
 int gettt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gray2black (TYPE_7__*) ; 
 int /*<<< orphan*/  isgray (TYPE_7__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_isreadonly (TYPE_6__*) ; 
 int sizeCclosure (int /*<<< orphan*/ ) ; 
 int sizeLclosure (int /*<<< orphan*/ ) ; 
 int sizenode (TYPE_5__*) ; 
 int /*<<< orphan*/  traverseclosure (TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  traverseproto (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  traversestack (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  traversetable (TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static l_mem propagatemark (global_State *g) {
  GCObject *o = g->gray;
  lua_assert(isgray(o));
  gray2black(o);
  switch (gettt(&o->gch)) {
    case LUA_TTABLE: {
      Table *h = gco2h(o);
      g->gray = h->gclist;
      if (traversetable(g, h))  /* table is weak? */
        black2gray(o);  /* keep it gray */
      return sizeof(Table) + sizeof(TValue) * h->sizearray +
                             sizeof(Node) * sizenode(h);
    }
    case LUA_TFUNCTION: {
      Closure *cl = gco2cl(o);
      g->gray = cl->c.gclist;
      traverseclosure(g, cl);
      return (cl->c.isC) ? sizeCclosure(cl->c.nupvalues) :
                           sizeLclosure(cl->l.nupvalues);
    }
    case LUA_TTHREAD: {
      lua_State *th = gco2th(o);
      g->gray = th->gclist;
      th->gclist = g->grayagain;
      g->grayagain = o;
      black2gray(o);
      traversestack(g, th);
      return sizeof(lua_State) + sizeof(TValue) * th->stacksize +
                                 sizeof(CallInfo) * th->size_ci;
    }
    case LUA_TPROTO: {
      Proto *p = gco2p(o);
      g->gray = p->gclist;
      traverseproto(g, p);

      return sizeof(Proto) + sizeof(Proto *) * p->sizep +
                             sizeof(TValue) * p->sizek +
                             sizeof(LocVar) * p->sizelocvars +
                             sizeof(TString *) * p->sizeupvalues +
                             (proto_isreadonly(p) ? 0 : sizeof(Instruction) * p->sizecode +
#ifdef LUA_OPTIMIZE_DEBUG
                                                         (p->packedlineinfo ?
                                                            c_strlen(cast(char *, p->packedlineinfo))+1 :
                                                            0));
#else
                                                         sizeof(int) * p->sizelineinfo);
#endif
    }
    default: lua_assert(0); return 0;
  }
}