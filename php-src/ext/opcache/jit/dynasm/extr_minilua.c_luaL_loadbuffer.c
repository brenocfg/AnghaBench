#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char const* s; size_t size; } ;
typedef  TYPE_1__ LoadS ;

/* Variables and functions */
 int /*<<< orphan*/  getS ; 
 int lua_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 

__attribute__((used)) static int luaL_loadbuffer(lua_State*L,const char*buff,size_t size,
const char*name){
LoadS ls;
ls.s=buff;
ls.size=size;
return lua_load(L,getS,&ls,name);
}