#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  info; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
struct TYPE_8__ {scalar_t__ k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETARG_B (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VCALL ; 
 scalar_t__ VNONRELOC ; 
 scalar_t__ VRELOCABLE ; 
 scalar_t__ VVARARG ; 
 int /*<<< orphan*/  getcode (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void luaK_setoneret(FuncState*fs,expdesc*e){
if(e->k==VCALL){
e->k=VNONRELOC;
e->u.s.info=GETARG_A(getcode(fs,e));
}
else if(e->k==VVARARG){
SETARG_B(getcode(fs,e),2);
e->k=VRELOCABLE;
}
}