#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct loopinfo {int type; int /*<<< orphan*/  acc; int /*<<< orphan*/  ensure_level; struct loopinfo* prev; scalar_t__ pc3; scalar_t__ pc2; scalar_t__ pc1; scalar_t__ pc0; } ;
typedef  enum looptype { ____Placeholder_looptype } looptype ;
struct TYPE_4__ {struct loopinfo* loop; int /*<<< orphan*/  ensure_level; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 scalar_t__ codegen_palloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cursp () ; 

__attribute__((used)) static struct loopinfo*
loop_push(codegen_scope *s, enum looptype t)
{
  struct loopinfo *p = (struct loopinfo *)codegen_palloc(s, sizeof(struct loopinfo));

  p->type = t;
  p->pc0 = p->pc1 = p->pc2 = p->pc3 = 0;
  p->prev = s->loop;
  p->ensure_level = s->ensure_level;
  p->acc = cursp();
  s->loop = p;

  return p;
}