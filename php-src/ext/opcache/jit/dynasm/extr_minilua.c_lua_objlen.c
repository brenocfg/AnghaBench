#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {size_t len; } ;
struct TYPE_3__ {size_t len; } ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  hvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index2adr (int /*<<< orphan*/ *,int) ; 
 size_t luaH_getn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaV_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* tsvalue (int /*<<< orphan*/ ) ; 
 int ttype (int /*<<< orphan*/ ) ; 
 TYPE_1__* uvalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t lua_objlen(lua_State*L,int idx){
StkId o=index2adr(L,idx);
switch(ttype(o)){
case 4:return tsvalue(o)->len;
case 7:return uvalue(o)->len;
case 5:return luaH_getn(hvalue(o));
case 3:{
size_t l;
l=(luaV_tostring(L,o)?tsvalue(o)->len:0);
return l;
}
default:return 0;
}
}