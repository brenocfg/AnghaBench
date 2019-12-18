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
struct TYPE_8__ {scalar_t__ nCharOfs; TYPE_4__* prev_para; TYPE_4__* next_para; } ;
struct TYPE_9__ {TYPE_1__ para; } ;
struct TYPE_11__ {TYPE_2__ member; struct TYPE_11__* next; struct TYPE_11__* prev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pCharStyle; TYPE_4__* pLast; TYPE_4__* pFirst; } ;
typedef  TYPE_3__ ME_TextBuffer ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 TYPE_4__* ME_MakeDI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diTextEnd ; 
 int /*<<< orphan*/  diTextStart ; 
 TYPE_3__* heap_alloc (int) ; 

__attribute__((used)) static ME_TextBuffer *ME_MakeText(void) {
  ME_TextBuffer *buf = heap_alloc(sizeof(*buf));
  ME_DisplayItem *p1 = ME_MakeDI(diTextStart);
  ME_DisplayItem *p2 = ME_MakeDI(diTextEnd);
  
  p1->prev = NULL;
  p1->next = p2;
  p2->prev = p1;
  p2->next = NULL;
  p1->member.para.next_para = p2;
  p2->member.para.prev_para = p1;
  p2->member.para.nCharOfs = 0;  
  
  buf->pFirst = p1;
  buf->pLast = p2;
  buf->pCharStyle = NULL;
  
  return buf;
}