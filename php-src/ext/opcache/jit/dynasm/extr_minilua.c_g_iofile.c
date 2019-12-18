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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fileerror (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** newfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tofile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g_iofile(lua_State*L,int f,const char*mode){
if(!lua_isnoneornil(L,1)){
const char*filename=lua_tostring(L,1);
if(filename){
FILE**pf=newfile(L);
*pf=fopen(filename,mode);
if(*pf==NULL)
fileerror(L,1,filename);
}
else{
tofile(L);
lua_pushvalue(L,1);
}
lua_rawseti(L,(-10001),f);
}
lua_rawgeti(L,(-10001),f);
return 1;
}