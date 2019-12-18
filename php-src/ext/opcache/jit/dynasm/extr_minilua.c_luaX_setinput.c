#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  ZIO ;
struct TYPE_5__ {int /*<<< orphan*/  token; } ;
struct TYPE_6__ {char decpoint; int linenumber; int lastline; int /*<<< orphan*/  buff; int /*<<< orphan*/ * L; int /*<<< orphan*/ * source; int /*<<< orphan*/ * fs; int /*<<< orphan*/ * z; TYPE_1__ lookahead; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_2__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_EOS ; 
 int /*<<< orphan*/  luaZ_resizebuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next (TYPE_2__*) ; 

__attribute__((used)) static void luaX_setinput(lua_State*L,LexState*ls,ZIO*z,TString*source){
ls->decpoint='.';
ls->L=L;
ls->lookahead.token=TK_EOS;
ls->z=z;
ls->fs=NULL;
ls->linenumber=1;
ls->lastline=1;
ls->source=source;
luaZ_resizebuffer(ls->L,ls->buff,32);
next(ls);
}