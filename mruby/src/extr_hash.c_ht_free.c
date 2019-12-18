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
struct TYPE_5__ {struct TYPE_5__* index; struct TYPE_5__* next; struct TYPE_5__* rootseg; } ;
typedef  TYPE_1__ segment ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  TYPE_1__ htable ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
ht_free(mrb_state *mrb, htable *t)
{
  segment *seg;

  if (!t) return;
  seg = t->rootseg;
  while (seg) {
    segment *p = seg;
    seg = seg->next;
    mrb_free(mrb, p);
  }
  if (t->index) mrb_free(mrb, t->index);
  mrb_free(mrb, t);
}