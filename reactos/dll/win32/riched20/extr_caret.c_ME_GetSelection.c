#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nOffset; } ;
struct TYPE_7__ {TYPE_2__* pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  TYPE_2__ ME_Cursor ;
typedef  int BOOL ;

/* Variables and functions */
 int ME_GetCursorOfs (TYPE_2__*) ; 
 int TRUE ; 

int ME_GetSelection(ME_TextEditor *editor, ME_Cursor **from, ME_Cursor **to)
{
  int from_ofs = ME_GetCursorOfs( &editor->pCursors[0] );
  int to_ofs   = ME_GetCursorOfs( &editor->pCursors[1] );
  BOOL swap = (from_ofs > to_ofs);

  if (from_ofs == to_ofs)
  {
      /* If cursor[0] is at the beginning of a run and cursor[1] at the end
         of the prev run then we need to swap. */
      if (editor->pCursors[0].nOffset < editor->pCursors[1].nOffset)
          swap = TRUE;
  }

  if (!swap)
  {
    *from = &editor->pCursors[0];
    *to = &editor->pCursors[1];
    return 0;
  } else {
    *from = &editor->pCursors[1];
    *to = &editor->pCursors[0];
    return 1;
  }
}