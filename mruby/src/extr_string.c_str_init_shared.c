#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* shared; int /*<<< orphan*/  capa; } ;
struct TYPE_7__ {TYPE_1__ aux; int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {TYPE_2__ heap; } ;
struct RString {TYPE_3__ as; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {int refcnt; int /*<<< orphan*/  capa; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ mrb_shared_string ;

/* Variables and functions */
 int /*<<< orphan*/  RSTR_SET_TYPE_FLAG (struct RString*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHARED ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct RString*
str_init_shared(mrb_state *mrb, const struct RString *orig, struct RString *s, mrb_shared_string *shared)
{
  if (shared) {
    shared->refcnt++;
  }
  else {
    shared = (mrb_shared_string *)mrb_malloc(mrb, sizeof(mrb_shared_string));
    shared->refcnt = 1;
    shared->ptr = orig->as.heap.ptr;
    shared->capa = orig->as.heap.aux.capa;
  }
  s->as.heap.ptr = orig->as.heap.ptr;
  s->as.heap.len = orig->as.heap.len;
  s->as.heap.aux.shared = shared;
  RSTR_SET_TYPE_FLAG(s, SHARED);
  return s;
}