#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
struct TYPE_7__ {int numparams; } ;
typedef  scalar_t__ StkId ;
typedef  TYPE_2__ Proto ;

/* Variables and functions */
 int /*<<< orphan*/  setnilvalue (scalar_t__) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static StkId adjust_varargs (lua_State *L, Proto *p, int actual) {
  int i;
  int nfixargs = p->numparams;
  StkId base, fixed;
  /* move fixed parameters to final position */
  fixed = L->top - actual;  /* first fixed argument */
  base = L->top;  /* final position of first argument */
  for (i = 0; i < nfixargs && i < actual; i++) {
    setobjs2s(L, L->top++, fixed + i);
    setnilvalue(fixed + i);  /* erase original copy (for GC) */
  }
  for (; i < nfixargs; i++)
    setnilvalue(L->top++);  /* complete missing arguments */
  return base;
}