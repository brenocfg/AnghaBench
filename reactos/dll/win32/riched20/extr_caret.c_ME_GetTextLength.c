#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int ME_GetCursorOfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetCursorToEnd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ME_GetTextLength(ME_TextEditor *editor)
{
  ME_Cursor cursor;
  ME_SetCursorToEnd(editor, &cursor, FALSE);
  return ME_GetCursorOfs(&cursor);
}