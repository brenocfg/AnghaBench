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
struct TYPE_6__ {int pc; int lasttarget; int nactvar; TYPE_1__* f; } ;
struct TYPE_5__ {int /*<<< orphan*/ * code; } ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_2__ FuncState ;

/* Variables and functions */
 int GETARG_A (int /*<<< orphan*/ ) ; 
 int GETARG_B (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_LOADNIL ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luaK_codeABC (TYPE_2__*,scalar_t__,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luaK_nil(FuncState*fs,int from,int n){
Instruction*previous;
if(fs->pc>fs->lasttarget){
if(fs->pc==0){
if(from>=fs->nactvar)
return;
}
else{
previous=&fs->f->code[fs->pc-1];
if(GET_OPCODE(*previous)==OP_LOADNIL){
int pfrom=GETARG_A(*previous);
int pto=GETARG_B(*previous);
if(pfrom<=from&&from<=pto+1){
if(from+n-1>pto)
SETARG_B(*previous,from+n-1);
return;
}
}
}
}
luaK_codeABC(fs,OP_LOADNIL,from,from+n-1,0);
}