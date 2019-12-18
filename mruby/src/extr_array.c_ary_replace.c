#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct RBasic {int dummy; } ;
struct TYPE_5__ {TYPE_4__* shared; scalar_t__ capa; } ;
struct TYPE_6__ {TYPE_1__ aux; scalar_t__ len; int /*<<< orphan*/ * ptr; } ;
struct TYPE_7__ {TYPE_2__ heap; } ;
struct RArray {TYPE_3__ as; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
struct TYPE_8__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ ARY_CAPA (struct RArray*) ; 
 scalar_t__ ARY_EMBED_P (struct RArray*) ; 
 scalar_t__ ARY_LEN (struct RArray*) ; 
 int /*<<< orphan*/  ARY_PTR (struct RArray*) ; 
 scalar_t__ ARY_REPLACE_SHARED_MIN ; 
 int /*<<< orphan*/  ARY_SET_LEN (struct RArray*,scalar_t__) ; 
 int /*<<< orphan*/  ARY_SET_SHARED_FLAG (struct RArray*) ; 
 scalar_t__ ARY_SHARED_P (struct RArray*) ; 
 int /*<<< orphan*/  ARY_UNSET_EMBED_FLAG (struct RArray*) ; 
 int /*<<< orphan*/  ARY_UNSET_SHARED_FLAG (struct RArray*) ; 
 int /*<<< orphan*/  array_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ary_expand_capa (int /*<<< orphan*/ *,struct RArray*,scalar_t__) ; 
 int /*<<< orphan*/  ary_make_shared (int /*<<< orphan*/ *,struct RArray*) ; 
 int /*<<< orphan*/  ary_modify_check (int /*<<< orphan*/ *,struct RArray*) ; 
 int /*<<< orphan*/  mrb_ary_decref (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_frozen_p (struct RArray*) ; 
 int /*<<< orphan*/  mrb_write_barrier (int /*<<< orphan*/ *,struct RBasic*) ; 

__attribute__((used)) static void
ary_replace(mrb_state *mrb, struct RArray *a, struct RArray *b)
{
  mrb_int len = ARY_LEN(b);

  ary_modify_check(mrb, a);
  if (a == b) return;
  if (ARY_SHARED_P(a)) {
    mrb_ary_decref(mrb, a->as.heap.aux.shared);
    a->as.heap.aux.capa = 0;
    a->as.heap.len = 0;
    a->as.heap.ptr = NULL;
    ARY_UNSET_SHARED_FLAG(a);
  }
  if (ARY_SHARED_P(b)) {
  shared_b:
    if (ARY_EMBED_P(a)) {
      ARY_UNSET_EMBED_FLAG(a);
    }
    else {
      mrb_free(mrb, a->as.heap.ptr);
    }
    a->as.heap.ptr = b->as.heap.ptr;
    a->as.heap.len = len;
    a->as.heap.aux.shared = b->as.heap.aux.shared;
    a->as.heap.aux.shared->refcnt++;
    ARY_SET_SHARED_FLAG(a);
    mrb_write_barrier(mrb, (struct RBasic*)a);
    return;
  }
  if (!mrb_frozen_p(b) && len > ARY_REPLACE_SHARED_MIN) {
    ary_make_shared(mrb, b);
    goto shared_b;
  }
  if (ARY_CAPA(a) < len)
    ary_expand_capa(mrb, a, len);
  array_copy(ARY_PTR(a), ARY_PTR(b), len);
  mrb_write_barrier(mrb, (struct RBasic*)a);
  ARY_SET_LEN(a, len);
}