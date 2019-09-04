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
struct TYPE_7__ {int /*<<< orphan*/ * ts; } ;
struct TYPE_8__ {TYPE_1__ seminfo; } ;
struct TYPE_9__ {TYPE_2__ t; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_3__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  TK_NAME ; 
 int /*<<< orphan*/  check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaX_next (TYPE_3__*) ; 

__attribute__((used)) static TString*str_checkname(LexState*ls){
TString*ts;
check(ls,TK_NAME);
ts=ls->t.seminfo.ts;
luaX_next(ls);
return ts;
}