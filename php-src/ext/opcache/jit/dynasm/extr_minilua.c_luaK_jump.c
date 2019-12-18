#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int jpc; } ;
typedef  TYPE_1__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  OP_JMP ; 
 int luaK_codeAsBx (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaK_concat (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int luaK_jump(FuncState*fs){
int jpc=fs->jpc;
int j;
fs->jpc=(-1);
j=luaK_codeAsBx(fs,OP_JMP,0,(-1));
luaK_concat(fs,&j,jpc);
return j;
}