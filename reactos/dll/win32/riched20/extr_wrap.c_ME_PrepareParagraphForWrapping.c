#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  editor; } ;
struct TYPE_12__ {TYPE_4__* next_para; scalar_t__ nRows; scalar_t__ nWidth; } ;
struct TYPE_13__ {int /*<<< orphan*/  run; TYPE_1__ para; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_2__ member; struct TYPE_15__* next; struct TYPE_15__* prev; } ;
struct TYPE_14__ {int /*<<< orphan*/  total_rows; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;
typedef  TYPE_5__ ME_Context ;

/* Variables and functions */
 scalar_t__ ME_CanJoinRuns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_DestroyDisplayItem (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_JoinRuns (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ME_Remove (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ diRun ; 
 scalar_t__ diStartRow ; 

__attribute__((used)) static void ME_PrepareParagraphForWrapping(ME_TextEditor *editor, ME_Context *c, ME_DisplayItem *tp) {
  ME_DisplayItem *p;

  tp->member.para.nWidth = 0;
  /* remove row start items as they will be reinserted by the
   * paragraph wrapper anyway */
  editor->total_rows -= tp->member.para.nRows;
  tp->member.para.nRows = 0;
  for (p = tp->next; p != tp->member.para.next_para; p = p->next) {
    if (p->type == diStartRow) {
      ME_DisplayItem *pRow = p;
      p = p->prev;
      ME_Remove(pRow);
      ME_DestroyDisplayItem(pRow);
    }
  }
  /* join runs that can be joined */
  for (p = tp->next; p != tp->member.para.next_para; p = p->next) {
    assert(p->type != diStartRow); /* should have been deleted above */
    if (p->type == diRun) {
      while (p->next->type == diRun && /* FIXME */
             ME_CanJoinRuns(&p->member.run, &p->next->member.run)) {
        ME_JoinRuns(c->editor, p);
      }
    }
  }
}