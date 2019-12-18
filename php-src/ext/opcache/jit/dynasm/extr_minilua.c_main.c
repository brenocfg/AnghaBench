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

/* Variables and functions */
 int /*<<< orphan*/  bitlib ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ luaL_loadfile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc,char**argv){
lua_State*L=luaL_newstate();
int i;
luaL_openlibs(L);
luaL_register(L,"bit",bitlib);
if(argc<2)return sizeof(void*);
lua_createtable(L,0,1);
lua_pushstring(L,argv[1]);
lua_rawseti(L,-2,0);
lua_setglobal(L,"arg");
if(luaL_loadfile(L,argv[1]))
goto err;
for(i=2;i<argc;i++)
lua_pushstring(L,argv[i]);
if(lua_pcall(L,argc-2,0,0)){
err:
fprintf(stderr,"Error: %s\n",lua_tostring(L,-1));
return 1;
}
lua_close(L);
return 0;
}