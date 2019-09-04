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
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int pushresult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_chars (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int read_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int test_eof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g_read(lua_State*L,FILE*f,int first){
int nargs=lua_gettop(L)-1;
int success;
int n;
clearerr(f);
if(nargs==0){
success=read_line(L,f);
n=first+1;
}
else{
luaL_checkstack(L,nargs+20,"too many arguments");
success=1;
for(n=first;nargs--&&success;n++){
if(lua_type(L,n)==3){
size_t l=(size_t)lua_tointeger(L,n);
success=(l==0)?test_eof(L,f):read_chars(L,f,l);
}
else{
const char*p=lua_tostring(L,n);
luaL_argcheck(L,p&&p[0]=='*',n,"invalid option");
switch(p[1]){
case'n':
success=read_number(L,f);
break;
case'l':
success=read_line(L,f);
break;
case'a':
read_chars(L,f,~((size_t)0));
success=1;
break;
default:
return luaL_argerror(L,n,"invalid format");
}
}
}
}
if(ferror(f))
return pushresult(L,0,NULL);
if(!success){
lua_pop(L,1);
lua_pushnil(L);
}
return n-first;
}