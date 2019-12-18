#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pCursors; } ;
typedef  TYPE_1__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  EDITSTREAM ;
typedef  int DWORD ;

/* Variables and functions */
 size_t ME_GetSelectionOfs (TYPE_1__*,int*,int*) ; 
 int ME_GetTextLength (TYPE_1__*) ; 
 int /*<<< orphan*/  ME_SetCursorToStart (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_StreamOutRange (TYPE_1__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int SFF_SELECTION ; 
 int SF_RTF ; 

LRESULT
ME_StreamOut(ME_TextEditor *editor, DWORD dwFormat, EDITSTREAM *stream)
{
  ME_Cursor start;
  int nChars;

  if (dwFormat & SFF_SELECTION) {
    int nStart, nTo;
    start = editor->pCursors[ME_GetSelectionOfs(editor, &nStart, &nTo)];
    nChars = nTo - nStart;
  } else {
    ME_SetCursorToStart(editor, &start);
    nChars = ME_GetTextLength(editor);
    /* Generate an end-of-paragraph at the end of SCF_ALL RTF output */
    if (dwFormat & SF_RTF)
      nChars++;
  }
  return ME_StreamOutRange(editor, dwFormat, &start, nChars, stream);
}