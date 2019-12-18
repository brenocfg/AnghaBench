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
struct TYPE_6__ {TYPE_3__* prev_para; } ;
struct TYPE_7__ {TYPE_1__ para; } ;
struct TYPE_8__ {scalar_t__ type; struct TYPE_8__* prev; TYPE_2__ member; } ;
typedef  TYPE_3__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 
 scalar_t__ diTextStart ; 

BOOL ME_PrevRun(ME_DisplayItem **para, ME_DisplayItem **run, BOOL all_para)
{
  ME_DisplayItem *p = (*run)->prev;
  while (p->type != diTextStart)
  {
    if (p->type == diParagraph) {
      if (!all_para) return FALSE;
      if (para && p->member.para.prev_para->type == diParagraph)
        *para = p->member.para.prev_para;
    } else if (p->type == diRun) {
      *run = p;
      return TRUE;
    }
    p = p->prev;
  }
  return FALSE;
}