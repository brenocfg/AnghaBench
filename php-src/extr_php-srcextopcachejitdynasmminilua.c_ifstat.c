#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ token; } ;
struct TYPE_9__ {TYPE_1__ t; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ LexState ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ TK_ELSE ; 
 scalar_t__ TK_ELSEIF ; 
 int /*<<< orphan*/  TK_END ; 
 int /*<<< orphan*/  TK_IF ; 
 int /*<<< orphan*/  block (TYPE_2__*) ; 
 int /*<<< orphan*/  check_match (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,int*,int) ; 
 int luaK_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaX_next (TYPE_2__*) ; 
 int test_then_block (TYPE_2__*) ; 

__attribute__((used)) static void ifstat(LexState*ls,int line){
FuncState*fs=ls->fs;
int flist;
int escapelist=(-1);
flist=test_then_block(ls);
while(ls->t.token==TK_ELSEIF){
luaK_concat(fs,&escapelist,luaK_jump(fs));
luaK_patchtohere(fs,flist);
flist=test_then_block(ls);
}
if(ls->t.token==TK_ELSE){
luaK_concat(fs,&escapelist,luaK_jump(fs));
luaK_patchtohere(fs,flist);
luaX_next(ls);
block(ls);
}
else
luaK_concat(fs,&escapelist,flist);
luaK_patchtohere(fs,escapelist);
check_match(ls,TK_END,TK_IF,line);
}