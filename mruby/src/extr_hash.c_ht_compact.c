#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; struct TYPE_10__* next; TYPE_1__* e; } ;
typedef  TYPE_3__ segment ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
struct TYPE_11__ {size_t size; size_t last_len; TYPE_2__* index; TYPE_3__* lastseg; TYPE_3__* rootseg; } ;
typedef  TYPE_4__ htable ;
struct TYPE_9__ {size_t size; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ht_index (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ht_compact(mrb_state *mrb, htable *t)
{
  segment *seg;
  mrb_int i;
  segment *seg2 = NULL;
  mrb_int i2;
  mrb_int size = 0;

  if (t == NULL) return;
  seg = t->rootseg;
  if (t->index && (size_t)t->size == t->index->size) {
    ht_index(mrb, t);
    return;
  }
  while (seg) {
    for (i=0; i<seg->size; i++) {
      mrb_value k = seg->e[i].key;

      if (!seg->next && i >= t->last_len) {
        goto exit;
      }
      if (mrb_undef_p(k)) {     /* found deleted key */
        if (seg2 == NULL) {
          seg2 = seg;
          i2 = i;
        }
      }
      else {
        size++;
        if (seg2 != NULL) {
          seg2->e[i2++] = seg->e[i];
          if (i2 >= seg2->size) {
            seg2 = seg2->next;
            i2 = 0;
          }
        }
      }
    }
    seg = seg->next;
  }
 exit:
  /* reached at end */
  t->size = size;
  if (seg2) {
    seg = seg2->next;
    seg2->next = NULL;
    t->last_len = i2;
    t->lastseg = seg2;
    while (seg) {
      seg2 = seg->next;
      mrb_free(mrb, seg);
      seg = seg2;
    }
  }
  if (t->index) {
    ht_index(mrb, t);
  }
}