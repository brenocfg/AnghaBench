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
struct TYPE_6__ {int /*<<< orphan*/ * prev_marked; int /*<<< orphan*/  next_marked; int /*<<< orphan*/  nFlags; int /*<<< orphan*/  fmt; } ;
struct TYPE_7__ {TYPE_1__ para; } ;
struct TYPE_8__ {TYPE_2__ member; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_3__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  MEPF_REWRAP ; 
 TYPE_3__* ME_MakeDI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_SetDefaultParaFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diParagraph ; 

__attribute__((used)) static ME_DisplayItem *make_para(ME_TextEditor *editor)
{
    ME_DisplayItem *item = ME_MakeDI(diParagraph);

    ME_SetDefaultParaFormat(editor, &item->member.para.fmt);
    item->member.para.nFlags = MEPF_REWRAP;
    item->member.para.next_marked = item->member.para.prev_marked = NULL;

    return item;
}