#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  info; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETARG_A (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * getjumpcontrol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void invertjump(FuncState*fs,expdesc*e){
Instruction*pc=getjumpcontrol(fs,e->u.s.info);
SETARG_A(*pc,!(GETARG_A(*pc)));
}