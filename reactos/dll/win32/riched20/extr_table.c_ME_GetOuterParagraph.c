#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nFlags; scalar_t__ pCell; TYPE_3__* prev_para; } ;
struct TYPE_10__ {TYPE_1__ para; } ;
struct TYPE_11__ {TYPE_2__ member; } ;
typedef  TYPE_3__ ME_DisplayItem ;

/* Variables and functions */
 int MEPF_ROWEND ; 
 TYPE_3__* ME_FindItemBack (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* ME_GetTableRowStart (TYPE_3__*) ; 
 int /*<<< orphan*/  diParagraph ; 

ME_DisplayItem* ME_GetOuterParagraph(ME_DisplayItem *para)
{
  if (para->member.para.nFlags & MEPF_ROWEND)
    para = para->member.para.prev_para;
  while (para->member.para.pCell)
  {
    para = ME_GetTableRowStart(para);
    if (!para->member.para.pCell)
      break;
    para = ME_FindItemBack(para->member.para.pCell, diParagraph);
  }
  return para;
}