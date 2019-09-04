#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ k; } ;
struct ConsControl {int tostore; int /*<<< orphan*/  na; TYPE_1__* t; TYPE_4__ v; } ;
struct TYPE_7__ {int /*<<< orphan*/  info; } ;
struct TYPE_6__ {TYPE_3__ s; } ;
struct TYPE_5__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ VVOID ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  luaK_setlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void closelistfield(FuncState*fs,struct ConsControl*cc){
if(cc->v.k==VVOID)return;
luaK_exp2nextreg(fs,&cc->v);
cc->v.k=VVOID;
if(cc->tostore==50){
luaK_setlist(fs,cc->t->u.s.info,cc->na,cc->tostore);
cc->tostore=0;
}
}