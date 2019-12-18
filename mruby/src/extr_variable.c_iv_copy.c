#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/ * val; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ segment ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_8__ {size_t last_len; TYPE_1__* rootseg; } ;
typedef  TYPE_2__ iv_tbl ;

/* Variables and functions */
 size_t MRB_IV_SEGMENT_SIZE ; 
 TYPE_2__* iv_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iv_put (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static iv_tbl*
iv_copy(mrb_state *mrb, iv_tbl *t)
{
  segment *seg;
  iv_tbl *t2;

  size_t i;

  seg = t->rootseg;
  t2 = iv_new(mrb);

  while (seg != NULL) {
    for (i=0; i<MRB_IV_SEGMENT_SIZE; i++) {
      mrb_sym key = seg->key[i];
      mrb_value val = seg->val[i];

      if ((seg->next == NULL) && (i >= t->last_len)) {
        return t2;
      }
      iv_put(mrb, t2, key, val);
    }
    seg = seg->next;
  }
  return t2;
}