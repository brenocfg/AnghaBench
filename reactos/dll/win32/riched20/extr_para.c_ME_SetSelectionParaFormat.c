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
struct TYPE_8__ {TYPE_2__* next_para; } ;
struct TYPE_6__ {TYPE_3__ para; } ;
struct TYPE_7__ {TYPE_1__ member; } ;
typedef  int /*<<< orphan*/  PARAFORMAT2 ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_2__ ME_DisplayItem ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ME_GetSelectionParas (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  ME_SetParaFormat (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL ME_SetSelectionParaFormat(ME_TextEditor *editor, const PARAFORMAT2 *pFmt)
{
  ME_DisplayItem *para, *para_end;

  ME_GetSelectionParas(editor, &para, &para_end);

  do {
    ME_SetParaFormat(editor, &para->member.para, pFmt);
    if (para == para_end)
      break;
    para = para->member.para.next_para;
  } while(1);

  return TRUE;
}