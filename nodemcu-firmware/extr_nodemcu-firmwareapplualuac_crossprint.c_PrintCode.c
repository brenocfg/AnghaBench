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
struct TYPE_5__ {int sizecode; int /*<<< orphan*/ * p; int /*<<< orphan*/ * k; int /*<<< orphan*/ * upvalues; int /*<<< orphan*/  sizeupvalues; scalar_t__* code; } ;
typedef  TYPE_1__ Proto ;
typedef  size_t OpCode ;
typedef  scalar_t__ Instruction ;

/* Variables and functions */
 int GETARG_A (scalar_t__) ; 
 int GETARG_B (scalar_t__) ; 
 int GETARG_Bx (scalar_t__) ; 
 int GETARG_C (scalar_t__) ; 
 int GETARG_sBx (scalar_t__) ; 
 size_t GET_OPCODE (scalar_t__) ; 
 int INDEXK (int) ; 
 int /*<<< orphan*/  ISK (int) ; 
#define  OP_ADD 151 
#define  OP_CLOSURE 150 
#define  OP_DIV 149 
#define  OP_EQ 148 
#define  OP_FORLOOP 147 
#define  OP_FORPREP 146 
#define  OP_GETGLOBAL 145 
#define  OP_GETTABLE 144 
#define  OP_GETUPVAL 143 
#define  OP_JMP 142 
#define  OP_LE 141 
#define  OP_LOADK 140 
#define  OP_LT 139 
#define  OP_MUL 138 
#define  OP_POW 137 
#define  OP_SELF 136 
#define  OP_SETGLOBAL 135 
#define  OP_SETLIST 134 
#define  OP_SETTABLE 133 
#define  OP_SETUPVAL 132 
#define  OP_SUB 131 
 int /*<<< orphan*/  OpArgK ; 
 int /*<<< orphan*/  OpArgN ; 
 int /*<<< orphan*/  PrintConstant (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  VOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getBMode (size_t) ; 
 int /*<<< orphan*/  getCMode (size_t) ; 
 int getOpMode (size_t) ; 
 int getline (TYPE_1__ const*,int) ; 
 char* getstr (int /*<<< orphan*/ ) ; 
#define  iABC 130 
#define  iABx 129 
#define  iAsBx 128 
 char** luaP_opnames ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* svalue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PrintCode(const Proto* f)
{
 const Instruction* code=f->code;
 int pc,n=f->sizecode;
 for (pc=0; pc<n; pc++)
 {
  Instruction i=code[pc];
  OpCode o=GET_OPCODE(i);
  int a=GETARG_A(i);
  int b=GETARG_B(i);
  int c=GETARG_C(i);
  int bx=GETARG_Bx(i);
  int sbx=GETARG_sBx(i);
  int line=getline(f,pc);
  printf("\t%d\t",pc+1);
  if (line>0) printf("[%d]\t",line); else printf("[-]\t");
  printf("%-9s\t",luaP_opnames[o]);
  switch (getOpMode(o))
  {
   case iABC:
    printf("%d",a);
    if (getBMode(o)!=OpArgN) printf(" %d",ISK(b) ? (-1-INDEXK(b)) : b);
    if (getCMode(o)!=OpArgN) printf(" %d",ISK(c) ? (-1-INDEXK(c)) : c);
    break;
   case iABx:
    if (getBMode(o)==OpArgK) printf("%d %d",a,-1-bx); else printf("%d %d",a,bx);
    break;
   case iAsBx:
    if (o==OP_JMP) printf("%d",sbx); else printf("%d %d",a,sbx);
    break;
  }
  switch (o)
  {
   case OP_LOADK:
    printf("\t; "); PrintConstant(f,bx);
    break;
   case OP_GETUPVAL:
   case OP_SETUPVAL:
    printf("\t; %s", (f->sizeupvalues>0) ? getstr(f->upvalues[b]) : "-");
    break;
   case OP_GETGLOBAL:
   case OP_SETGLOBAL:
    printf("\t; %s",svalue(&f->k[bx]));
    break;
   case OP_GETTABLE:
   case OP_SELF:
    if (ISK(c)) { printf("\t; "); PrintConstant(f,INDEXK(c)); }
    break;
   case OP_SETTABLE:
   case OP_ADD:
   case OP_SUB:
   case OP_MUL:
   case OP_DIV:
   case OP_POW:
   case OP_EQ:
   case OP_LT:
   case OP_LE:
    if (ISK(b) || ISK(c))
    {
     printf("\t; ");
     if (ISK(b)) PrintConstant(f,INDEXK(b)); else printf("-");
     printf(" ");
     if (ISK(c)) PrintConstant(f,INDEXK(c)); else printf("-");
    }
    break;
   case OP_JMP:
   case OP_FORLOOP:
   case OP_FORPREP:
    printf("\t; to %d",sbx+pc+2);
    break;
   case OP_CLOSURE:
    printf("\t; %p",VOID(f->p[bx]));
    break;
   case OP_SETLIST:
    if (c==0) printf("\t; %d",(int)code[++pc]);
    else printf("\t; %d",c);
    break;
   default:
    break;
  }
  printf("\n");
 }
}