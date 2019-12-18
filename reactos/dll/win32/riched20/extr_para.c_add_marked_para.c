#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nCharOfs; TYPE_4__* next_marked; TYPE_4__* prev_marked; } ;
struct TYPE_8__ {TYPE_1__ para; } ;
struct TYPE_10__ {TYPE_2__ member; } ;
struct TYPE_9__ {TYPE_4__* first_marked_para; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */

void add_marked_para(ME_TextEditor *editor, ME_DisplayItem *di)
{
    ME_DisplayItem *iter = editor->first_marked_para;

    if (!iter)
    {
        editor->first_marked_para = di;
        return;
    }
    while (iter)
    {
        if (iter == di)
            return;
        else if (di->member.para.nCharOfs < iter->member.para.nCharOfs)
        {
            if (iter == editor->first_marked_para)
                editor->first_marked_para = di;
            di->member.para.next_marked = iter;
            iter->member.para.prev_marked = di;
            break;
        }
        else if (di->member.para.nCharOfs >= iter->member.para.nCharOfs)
        {
            if (!iter->member.para.next_marked || di->member.para.nCharOfs < iter->member.para.next_marked->member.para.nCharOfs)
            {
                if (iter->member.para.next_marked)
                {
                    di->member.para.next_marked = iter->member.para.next_marked;
                    iter->member.para.next_marked->member.para.prev_marked = di;
                }
                di->member.para.prev_marked = iter;
                iter->member.para.next_marked = di;
                break;
            }
        }
        iter = iter->member.para.next_marked;
    }
}