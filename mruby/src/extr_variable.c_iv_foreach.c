#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* key; struct TYPE_4__* next; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ segment ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ (* mrb_iv_foreach_func ) (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,void*) ;
struct TYPE_5__ {size_t last_len; TYPE_1__* rootseg; } ;
typedef  TYPE_2__ iv_tbl ;

/* Variables and functions */
 size_t MRB_IV_SEGMENT_SIZE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
iv_foreach(mrb_state *mrb, iv_tbl *t, mrb_iv_foreach_func *func, void *p)
{
  segment *seg;
  size_t i;

  if (t == NULL) return;
  seg = t->rootseg;
  while (seg) {
    for (i=0; i<MRB_IV_SEGMENT_SIZE; i++) {
      mrb_sym key = seg->key[i];

      /* no value in last segment after last_len */
      if (!seg->next && i >= t->last_len) {
        return;
      }
      if (key != 0) {
        if ((*func)(mrb, key, seg->val[i], p) != 0) {
          return;
        }
      }
    }
    seg = seg->next;
  }
  return;
}