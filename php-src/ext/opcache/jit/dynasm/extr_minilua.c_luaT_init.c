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
struct TYPE_2__ {int /*<<< orphan*/ * tmname; } ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 int TM_N ; 
 int /*<<< orphan*/  luaS_fix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaS_new (int /*<<< orphan*/ *,char const* const) ; 

__attribute__((used)) static void luaT_init(lua_State*L){
static const char*const luaT_eventname[]={
"__index","__newindex",
"__gc","__mode","__eq",
"__add","__sub","__mul","__div","__mod",
"__pow","__unm","__len","__lt","__le",
"__concat","__call"
};
int i;
for(i=0;i<TM_N;i++){
G(L)->tmname[i]=luaS_new(L,luaT_eventname[i]);
luaS_fix(G(L)->tmname[i]);
}
}