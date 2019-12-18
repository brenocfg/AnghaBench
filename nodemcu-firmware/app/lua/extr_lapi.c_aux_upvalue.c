#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__** upvals; TYPE_4__* p; } ;
struct TYPE_7__ {int nupvalues; int /*<<< orphan*/ * upvalue; scalar_t__ isC; } ;
struct TYPE_11__ {TYPE_3__ l; TYPE_1__ c; } ;
struct TYPE_10__ {int sizeupvalues; int /*<<< orphan*/ * upvalues; } ;
struct TYPE_8__ {int /*<<< orphan*/ * v; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  StkId ;
typedef  TYPE_4__ Proto ;
typedef  TYPE_5__ Closure ;

/* Variables and functions */
 TYPE_5__* clvalue (int /*<<< orphan*/ ) ; 
 char const* getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttisfunction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *aux_upvalue (StkId fi, int n, TValue **val) {
  Closure *f;
  if (!ttisfunction(fi)) return NULL;
  f = clvalue(fi);
  if (f->c.isC) {
    if (!(1 <= n && n <= f->c.nupvalues)) return NULL;
    *val = &f->c.upvalue[n-1];
    return "";
  }
  else {
    Proto *p = f->l.p;
    if (!(1 <= n && n <= p->sizeupvalues)) return NULL;
    *val = f->l.upvals[n-1]->v;
    return getstr(p->upvalues[n-1]);
  }
}