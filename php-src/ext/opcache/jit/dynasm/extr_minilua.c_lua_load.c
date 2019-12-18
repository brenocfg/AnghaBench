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
typedef  int /*<<< orphan*/  lua_Reader ;
typedef  int /*<<< orphan*/  ZIO ;

/* Variables and functions */
 int luaD_protectedparser (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaZ_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int lua_load(lua_State*L,lua_Reader reader,void*data,
const char*chunkname){
ZIO z;
int status;
if(!chunkname)chunkname="?";
luaZ_init(L,&z,reader,data);
status=luaD_protectedparser(L,&z,chunkname);
return status;
}