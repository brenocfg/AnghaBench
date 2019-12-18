#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pos; int len; int /*<<< orphan*/  fmt; } ;
struct TYPE_4__ {TYPE_1__ set_char_fmt; } ;
struct undo_item {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  CHARFORMAT2W ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct undo_item* add_undo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  undo_set_char_fmt ; 

BOOL add_undo_set_char_fmt( ME_TextEditor *editor, int pos, int len, const CHARFORMAT2W *fmt )
{
    struct undo_item *undo = add_undo( editor, undo_set_char_fmt );
    if (!undo) return FALSE;

    undo->u.set_char_fmt.pos = pos;
    undo->u.set_char_fmt.len = len;
    undo->u.set_char_fmt.fmt = *fmt;

    return TRUE;
}