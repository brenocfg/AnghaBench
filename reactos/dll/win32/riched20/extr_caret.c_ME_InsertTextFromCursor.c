#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_24__ {scalar_t__ nOffset; TYPE_4__* pRun; TYPE_4__* pPara; } ;
struct TYPE_20__ {scalar_t__ len; } ;
struct TYPE_21__ {TYPE_1__ run; } ;
struct TYPE_23__ {TYPE_2__ member; } ;
struct TYPE_22__ {int nModifyStep; int nCursors; int nTextLimit; int styleFlags; TYPE_5__* pCursors; int /*<<< orphan*/  bEmulateVersion10; } ;
typedef  TYPE_3__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_4__ ME_DisplayItem ;
typedef  TYPE_5__ ME_Cursor ;

/* Variables and functions */
 int ES_MULTILINE ; 
 int /*<<< orphan*/  MERF_TAB ; 
 int /*<<< orphan*/  ME_DeleteSelection (TYPE_3__*) ; 
 TYPE_4__* ME_FindItemBack (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ME_FindItemFwd (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ME_GetTextLength (TYPE_3__*) ; 
 int /*<<< orphan*/  ME_InternalInsertTextFromCursor (TYPE_3__*,int,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ME_IsSelection (TYPE_3__*) ; 
 TYPE_4__* ME_SplitParagraph (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_SplitRunSimple (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  diRun ; 
 int lstrlenW (char const*) ; 

void ME_InsertTextFromCursor(ME_TextEditor *editor, int nCursor, 
  const WCHAR *str, int len, ME_Style *style)
{
  const WCHAR *pos;
  ME_Cursor *p = NULL;
  int oldLen;

  /* FIXME really HERE ? */
  if (ME_IsSelection(editor))
    ME_DeleteSelection(editor);

  /* FIXME: is this too slow? */
  /* Didn't affect performance for WM_SETTEXT (around 50sec/30K) */
  oldLen = ME_GetTextLength(editor);

  /* text operations set modified state */
  editor->nModifyStep = 1;

  assert(style);

  assert(nCursor>=0 && nCursor<editor->nCursors);
  if (len == -1)
    len = lstrlenW(str);

  /* grow the text limit to fit our text */
  if(editor->nTextLimit < oldLen +len)
    editor->nTextLimit = oldLen + len;

  pos = str;

  while (len)
  {
    /* FIXME this sucks - no respect for unicode (what else can be a line separator in unicode?) */
    while(pos - str < len && *pos != '\r' && *pos != '\n' && *pos != '\t')
      pos++;

    if (pos != str) { /* handle text */
      ME_InternalInsertTextFromCursor(editor, nCursor, str, pos-str, style, 0);
    } else if (*pos == '\t') { /* handle tabs */
      WCHAR tab = '\t';
      ME_InternalInsertTextFromCursor(editor, nCursor, &tab, 1, style, MERF_TAB);
      pos++;
    } else { /* handle EOLs */
      ME_DisplayItem *tp, *end_run, *run, *prev;
      int eol_len = 0;

      /* Check if new line is allowed for this control */
      if (!(editor->styleFlags & ES_MULTILINE))
        break;

      /* Find number of CR and LF in end of paragraph run */
      if (*pos =='\r')
      {
        if (len > 1 && pos[1] == '\n')
          eol_len = 2;
        else if (len > 2 && pos[1] == '\r' && pos[2] == '\n')
          eol_len = 3;
        else
          eol_len = 1;
      } else {
        assert(*pos == '\n');
        eol_len = 1;
      }
      pos += eol_len;

      if (!editor->bEmulateVersion10 && eol_len == 3)
      {
        /* handle special \r\r\n sequence (richedit 2.x and higher only) */
        WCHAR space = ' ';
        ME_InternalInsertTextFromCursor(editor, nCursor, &space, 1, style, 0);
      } else {
        const WCHAR cr = '\r', *eol_str = str;

        if (!editor->bEmulateVersion10)
        {
          eol_str = &cr;
          eol_len = 1;
        }

        p = &editor->pCursors[nCursor];

        if (p->nOffset == p->pRun->member.run.len)
        {
           run = ME_FindItemFwd( p->pRun, diRun );
           if (!run) run = p->pRun;
        }
        else
        {
          if (p->nOffset) ME_SplitRunSimple(editor, p);
          run = p->pRun;
        }

        tp = ME_SplitParagraph(editor, run, style, eol_str, eol_len, 0);

        end_run = ME_FindItemBack(tp, diRun);

        /* Move any cursors that were at the end of the previous run to the beginning of the new para */
        prev = ME_FindItemBack( end_run, diRun );
        if (prev)
        {
          int i;
          for (i = 0; i < editor->nCursors; i++)
          {
            if (editor->pCursors[i].pRun == prev &&
                editor->pCursors[i].nOffset == prev->member.run.len)
            {
              editor->pCursors[i].pPara = tp;
              editor->pCursors[i].pRun = run;
              editor->pCursors[i].nOffset = 0;
            }
          }
        }

      }
    }
    len -= pos - str;
    str = pos;
  }
}