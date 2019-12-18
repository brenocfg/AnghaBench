#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  aux; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {int /*<<< orphan*/  k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  VINDEXED ; 
 int /*<<< orphan*/  luaK_exp2RK (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void luaK_indexed(FuncState*fs,expdesc*t,expdesc*k){
t->u.s.aux=luaK_exp2RK(fs,k);
t->k=VINDEXED;
}