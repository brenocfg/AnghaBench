#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {size_t len; } ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  index2adr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaC_checkGC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaV_tostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* svalue (int /*<<< orphan*/ ) ; 
 TYPE_1__* tsvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttisstring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*lua_tolstring(lua_State*L,int idx,size_t*len){
StkId o=index2adr(L,idx);
if(!ttisstring(o)){
if(!luaV_tostring(L,o)){
if(len!=NULL)*len=0;
return NULL;
}
luaC_checkGC(L);
o=index2adr(L,idx);
}
if(len!=NULL)*len=tsvalue(o)->len;
return svalue(o);
}