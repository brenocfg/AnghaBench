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
struct TYPE_4__ {scalar_t__* key; struct TYPE_4__* next; void** val; } ;
typedef  TYPE_1__ segment ;
typedef  void* mrb_value ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {size_t last_len; TYPE_1__* rootseg; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ iv_tbl ;

/* Variables and functions */
 size_t MRB_IV_SEGMENT_SIZE ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
iv_put(mrb_state *mrb, iv_tbl *t, mrb_sym sym, mrb_value val)
{
  segment *seg;
  segment *prev = NULL;
  segment *matched_seg = NULL;
  size_t matched_idx = 0;
  size_t i;

  if (t == NULL) return;
  seg = t->rootseg;
  while (seg) {
    for (i=0; i<MRB_IV_SEGMENT_SIZE; i++) {
      mrb_sym key = seg->key[i];
      /* Found room in last segment after last_len */
      if (!seg->next && i >= t->last_len) {
        seg->key[i] = sym;
        seg->val[i] = val;
        t->last_len = i+1;
        t->size++;
        return;
      }
      if (!matched_seg && key == 0) {
        matched_seg = seg;
        matched_idx = i;
      }
      else if (key == sym) {
        seg->val[i] = val;
        return;
      }
    }
    prev = seg;
    seg = seg->next;
  }

  /* Not found */
  if (matched_seg) {
    matched_seg->key[matched_idx] = sym;
    matched_seg->val[matched_idx] = val;
    t->size++;
    return;
  }

  seg = (segment*)mrb_malloc(mrb, sizeof(segment));
  seg->next = NULL;
  seg->key[0] = sym;
  seg->val[0] = val;
  t->last_len = 1;
  t->size++;
  if (prev) {
    prev->next = seg;
  }
  else {
    t->rootseg = seg;
  }
}