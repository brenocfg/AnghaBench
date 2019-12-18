#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int upval; int /*<<< orphan*/  breaklist; int /*<<< orphan*/  nactvar; struct TYPE_11__* previous; int /*<<< orphan*/  isbreakable; } ;
struct TYPE_10__ {TYPE_3__* bl; } ;
struct TYPE_9__ {TYPE_2__* fs; } ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ FuncState ;
typedef  TYPE_3__ BlockCnt ;

/* Variables and functions */
 int /*<<< orphan*/  OP_CLOSE ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_concat (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_jump (TYPE_2__*) ; 
 int /*<<< orphan*/  luaX_syntaxerror (TYPE_1__*,char*) ; 

__attribute__((used)) static void breakstat(LexState*ls){
FuncState*fs=ls->fs;
BlockCnt*bl=fs->bl;
int upval=0;
while(bl&&!bl->isbreakable){
upval|=bl->upval;
bl=bl->previous;
}
if(!bl)
luaX_syntaxerror(ls,"no loop to break");
if(upval)
luaK_codeABC(fs,OP_CLOSE,bl->nactvar,0,0);
luaK_concat(fs,&bl->breaklist,luaK_jump(fs));
}