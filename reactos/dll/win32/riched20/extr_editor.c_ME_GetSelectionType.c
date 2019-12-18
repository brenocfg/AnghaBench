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
struct TYPE_9__ {TYPE_3__* pRun; } ;
struct TYPE_6__ {scalar_t__ reobj; } ;
struct TYPE_7__ {TYPE_1__ run; } ;
struct TYPE_8__ {TYPE_2__ member; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_4__ ME_Cursor ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ME_CursorFromCharOfs (int /*<<< orphan*/ *,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ SEL_EMPTY ; 
 scalar_t__ SEL_MULTICHAR ; 
 scalar_t__ SEL_MULTIOBJECT ; 
 scalar_t__ SEL_OBJECT ; 
 scalar_t__ SEL_TEXT ; 

__attribute__((used)) static LONG ME_GetSelectionType(ME_TextEditor *editor)
{
    LONG sel_type = SEL_EMPTY;
    LONG start, end;

    ME_GetSelectionOfs(editor, &start, &end);
    if (start == end)
        sel_type = SEL_EMPTY;
    else
    {
        LONG object_count = 0, character_count = 0;
        int i;

        for (i = 0; i < end - start; i++)
        {
            ME_Cursor cursor;

            ME_CursorFromCharOfs(editor, start + i, &cursor);
            if (cursor.pRun->member.run.reobj)
                object_count++;
            else
                character_count++;
            if (character_count >= 2 && object_count >= 2)
                return (SEL_TEXT | SEL_MULTICHAR | SEL_OBJECT | SEL_MULTIOBJECT);
        }
        if (character_count)
        {
            sel_type |= SEL_TEXT;
            if (character_count >= 2)
                sel_type |= SEL_MULTICHAR;
        }
        if (object_count)
        {
            sel_type |= SEL_OBJECT;
            if (object_count >= 2)
                sel_type |= SEL_MULTIOBJECT;
        }
    }
    return sel_type;
}