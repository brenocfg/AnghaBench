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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchar (char const) ; 

__attribute__((used)) static int str_upper(lua_State*L){
size_t l;
size_t i;
luaL_Buffer b;
const char*s=luaL_checklstring(L,1,&l);
luaL_buffinit(L,&b);
for(i=0;i<l;i++)
luaL_addchar(&b,toupper(uchar(s[i])));
luaL_pushresult(&b);
return 1;
}