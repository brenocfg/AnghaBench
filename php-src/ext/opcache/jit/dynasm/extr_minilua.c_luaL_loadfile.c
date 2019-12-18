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
struct TYPE_3__ {int extraline; int /*<<< orphan*/ * f; } ;
typedef  TYPE_1__ LoadF ;

/* Variables and functions */
 int EOF ; 
 int errfile (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * freopen (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getF ; 
 int getc (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int luaL_loadfile(lua_State*L,const char*filename){
LoadF lf;
int status,readstatus;
int c;
int fnameindex=lua_gettop(L)+1;
lf.extraline=0;
if(filename==NULL){
lua_pushliteral(L,"=stdin");
lf.f=stdin;
}
else{
lua_pushfstring(L,"@%s",filename);
lf.f=fopen(filename,"r");
if(lf.f==NULL)return errfile(L,"open",fnameindex);
}
c=getc(lf.f);
if(c=='#'){
lf.extraline=1;
while((c=getc(lf.f))!=EOF&&c!='\n');
if(c=='\n')c=getc(lf.f);
}
if(c=="\033Lua"[0]&&filename){
lf.f=freopen(filename,"rb",lf.f);
if(lf.f==NULL)return errfile(L,"reopen",fnameindex);
while((c=getc(lf.f))!=EOF&&c!="\033Lua"[0]);
lf.extraline=0;
}
ungetc(c,lf.f);
status=lua_load(L,getF,&lf,lua_tostring(L,-1));
readstatus=ferror(lf.f);
if(filename)fclose(lf.f);
if(readstatus){
lua_settop(L,fnameindex);
return errfile(L,"read",fnameindex);
}
lua_remove(L,fnameindex);
return status;
}