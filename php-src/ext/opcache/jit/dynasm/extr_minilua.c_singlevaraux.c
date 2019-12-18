#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  info; } ;
struct TYPE_13__ {TYPE_1__ s; } ;
struct TYPE_14__ {int k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
struct TYPE_15__ {struct TYPE_15__* prev; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int VGLOBAL ; 
 int VLOCAL ; 
 int VUPVAL ; 
 int /*<<< orphan*/  indexupvalue (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  init_exp (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  markupval (TYPE_4__*,int) ; 
 int searchvar (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int singlevaraux(FuncState*fs,TString*n,expdesc*var,int base){
if(fs==NULL){
init_exp(var,VGLOBAL,((1<<8)-1));
return VGLOBAL;
}
else{
int v=searchvar(fs,n);
if(v>=0){
init_exp(var,VLOCAL,v);
if(!base)
markupval(fs,v);
return VLOCAL;
}
else{
if(singlevaraux(fs->prev,n,var,0)==VGLOBAL)
return VGLOBAL;
var->u.s.info=indexupvalue(fs,n,var);
var->k=VUPVAL;
return VUPVAL;
}
}
}