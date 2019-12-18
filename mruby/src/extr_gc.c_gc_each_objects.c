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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ mrb_heap_page ;
struct TYPE_10__ {TYPE_2__* heaps; } ;
typedef  TYPE_3__ mrb_gc ;
typedef  scalar_t__ (* mrb_each_object_callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;
struct TYPE_8__ {int /*<<< orphan*/  basic; } ;
struct TYPE_11__ {TYPE_1__ as; } ;
typedef  TYPE_4__ RVALUE ;

/* Variables and functions */
 scalar_t__ MRB_EACH_OBJ_BREAK ; 
 int MRB_HEAP_PAGE_SIZE ; 
 TYPE_4__* objects (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
gc_each_objects(mrb_state *mrb, mrb_gc *gc, mrb_each_object_callback *callback, void *data)
{
  mrb_heap_page* page;

  page = gc->heaps;
  while (page != NULL) {
    RVALUE *p;
    int i;

    p = objects(page);
    for (i=0; i < MRB_HEAP_PAGE_SIZE; i++) {
      if ((*callback)(mrb, &p[i].as.basic, data) == MRB_EACH_OBJ_BREAK)
        return;
    }
    page = page->next;
  }
}