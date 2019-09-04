#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct SParser {char const* name; int /*<<< orphan*/  buff; int /*<<< orphan*/ * z; } ;
struct TYPE_7__ {int /*<<< orphan*/  errfunc; int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  ZIO ;

/* Variables and functions */
 int /*<<< orphan*/  f_parser ; 
 int luaD_pcall (TYPE_1__*,int /*<<< orphan*/ ,struct SParser*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaZ_freebuffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaZ_initbuffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savestack (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int luaD_protectedparser(lua_State*L,ZIO*z,const char*name){
struct SParser p;
int status;
p.z=z;p.name=name;
luaZ_initbuffer(L,&p.buff);
status=luaD_pcall(L,f_parser,&p,savestack(L,L->top),L->errfunc);
luaZ_freebuffer(L,&p.buff);
return status;
}