#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 int ME_GetCursorOfs (int /*<<< orphan*/ *) ; 

int ME_GetSelectionOfs(ME_TextEditor *editor, int *from, int *to)
{
  *from = ME_GetCursorOfs(&editor->pCursors[0]);
  *to =   ME_GetCursorOfs(&editor->pCursors[1]);

  if (*from > *to)
  {
    int tmp = *from;
    *from = *to;
    *to = tmp;
    return 1;
  }
  return 0;
}