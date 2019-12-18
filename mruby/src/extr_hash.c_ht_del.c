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
struct TYPE_7__ {size_t size; struct TYPE_7__* next; TYPE_1__* e; } ;
typedef  TYPE_2__ segment ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_8__ {size_t last_len; int /*<<< orphan*/  size; TYPE_2__* rootseg; } ;
typedef  TYPE_3__ htable ;
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ht_hash_equal (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_value () ; 

__attribute__((used)) static mrb_bool
ht_del(mrb_state *mrb, htable *t, mrb_value key, mrb_value *vp)
{
  segment *seg;
  mrb_int i;

  if (t == NULL) return FALSE;
  seg = t->rootseg;
  while (seg) {
    for (i=0; i<seg->size; i++) {
      mrb_value key2;

      if (!seg->next && i >= t->last_len) {
        /* not found */
        return FALSE;
      }
      key2 = seg->e[i].key;
      if (!mrb_undef_p(key2) && ht_hash_equal(mrb, t, key, key2)) {
        if (vp) *vp = seg->e[i].val;
        seg->e[i].key = mrb_undef_value();
        t->size--;
        return TRUE;
      }
    }
    seg = seg->next;
  }
  return FALSE;
}