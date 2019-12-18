#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; struct TYPE_9__* next; TYPE_1__* e; } ;
typedef  TYPE_2__ segment ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
struct TYPE_10__ {scalar_t__ size; size_t last_len; TYPE_2__* rootseg; } ;
typedef  TYPE_3__ htable ;
struct TYPE_8__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 TYPE_3__* ht_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ht_put (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static htable*
ht_copy(mrb_state *mrb, htable *t)
{
  segment *seg;
  htable *t2;
  mrb_int i;

  seg = t->rootseg;
  t2 = ht_new(mrb);
  if (t->size == 0) return t2;

  while (seg) {
    for (i=0; i<seg->size; i++) {
      mrb_value key = seg->e[i].key;
      mrb_value val = seg->e[i].val;

      if ((seg->next == NULL) && (i >= t->last_len)) {
        return t2;
      }
      if (mrb_undef_p(key)) continue; /* skip deleted key */
      ht_put(mrb, t2, key, val);
    }
    seg = seg->next;
  }
  return t2;
}