#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_15__ {int tt; } ;
struct TYPE_17__ {TYPE_1__ gch; } ;
struct TYPE_16__ {int /*<<< orphan*/  nuse; } ;
struct TYPE_14__ {TYPE_2__ strt; } ;
typedef  TYPE_3__ GCObject ;

/* Variables and functions */
 TYPE_13__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2cl (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2h (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2p (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2th (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2ts (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2u (TYPE_3__*) ; 
 int /*<<< orphan*/  gco2uv (TYPE_3__*) ; 
 int /*<<< orphan*/  luaE_freethread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeproto (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaF_freeupval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaH_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaM_freemem (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizestring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizeudata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeobj(lua_State*L,GCObject*o){
switch(o->gch.tt){
case(8+1):luaF_freeproto(L,gco2p(o));break;
case 6:luaF_freeclosure(L,gco2cl(o));break;
case(8+2):luaF_freeupval(L,gco2uv(o));break;
case 5:luaH_free(L,gco2h(o));break;
case 8:{
luaE_freethread(L,gco2th(o));
break;
}
case 4:{
G(L)->strt.nuse--;
luaM_freemem(L,o,sizestring(gco2ts(o)));
break;
}
case 7:{
luaM_freemem(L,o,sizeudata(gco2u(o)));
break;
}
default:;
}
}