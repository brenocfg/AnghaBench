#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;
typedef  int /*<<< orphan*/  BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  OP_FORLOOP ; 
 int /*<<< orphan*/  OP_FORPREP ; 
 int /*<<< orphan*/  OP_TFORLOOP ; 
 int /*<<< orphan*/  TK_DO ; 
 int /*<<< orphan*/  adjustlocalvars (TYPE_1__*,int) ; 
 int /*<<< orphan*/  block (TYPE_1__*) ; 
 int /*<<< orphan*/  checknext (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enterblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leaveblock (int /*<<< orphan*/ *) ; 
 int luaK_codeABC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int luaK_codeAsBx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  luaK_fixline (int /*<<< orphan*/ *,int) ; 
 int luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchlist (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaK_reserveregs (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void forbody(LexState*ls,int base,int line,int nvars,int isnum){
BlockCnt bl;
FuncState*fs=ls->fs;
int prep,endfor;
adjustlocalvars(ls,3);
checknext(ls,TK_DO);
prep=isnum?luaK_codeAsBx(fs,OP_FORPREP,base,(-1)):luaK_jump(fs);
enterblock(fs,&bl,0);
adjustlocalvars(ls,nvars);
luaK_reserveregs(fs,nvars);
block(ls);
leaveblock(fs);
luaK_patchtohere(fs,prep);
endfor=(isnum)?luaK_codeAsBx(fs,OP_FORLOOP,base,(-1)):
luaK_codeABC(fs,OP_TFORLOOP,base,0,nvars);
luaK_fixline(fs,line);
luaK_patchlist(fs,(isnum?endfor:luaK_jump(fs)),prep+1);
}