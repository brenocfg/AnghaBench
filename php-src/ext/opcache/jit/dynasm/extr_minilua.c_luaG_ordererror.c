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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  luaG_runerror (int /*<<< orphan*/ *,char*,char const*,...) ; 
 char** luaT_typenames ; 
 size_t ttype (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int luaG_ordererror(lua_State*L,const TValue*p1,const TValue*p2){
const char*t1=luaT_typenames[ttype(p1)];
const char*t2=luaT_typenames[ttype(p2)];
if(t1[2]==t2[2])
luaG_runerror(L,"attempt to compare two %s values",t1);
else
luaG_runerror(L,"attempt to compare %s with %s",t1,t2);
return 0;
}