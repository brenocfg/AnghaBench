#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  pPara; } ;
struct TYPE_15__ {int cbSize; scalar_t__ nPos; scalar_t__ nPage; scalar_t__ nMax; scalar_t__ nMin; } ;
struct TYPE_14__ {int cbSize; scalar_t__ nPos; scalar_t__ nPage; scalar_t__ nMax; scalar_t__ nMin; } ;
struct TYPE_13__ {scalar_t__ cpMax; scalar_t__ cpMin; } ;
struct TYPE_16__ {scalar_t__ cy; scalar_t__ cx; } ;
struct TYPE_17__ {int styleFlags; int nCursors; int nUDArrowX; int rgbBackColor; int nParagraphs; int mode; int bWordWrap; int /*<<< orphan*/  reobj_list; scalar_t__ wheel_remain; TYPE_4__ horz_si; TYPE_3__ vert_si; TYPE_2__ notified_cr; scalar_t__ cPasswordMask; int /*<<< orphan*/  nSelectionType; scalar_t__ selofs; int /*<<< orphan*/ * texthost; int /*<<< orphan*/  bDefaultFormatRect; int /*<<< orphan*/  rcFormat; TYPE_1__* pFontCache; void* bMouseCaptured; void* bDialogMode; void* bHaveFocus; void* AutoURLDetect_bEnable; int /*<<< orphan*/ * lpOleCallback; int /*<<< orphan*/ * pfnWordBreak; void* bHideSelection; TYPE_8__* pCursors; int /*<<< orphan*/  pLastSelEndPara; int /*<<< orphan*/  pLastSelStartPara; scalar_t__ nLastSelEnd; scalar_t__ nLastSelStart; int /*<<< orphan*/  nUndoMode; int /*<<< orphan*/  nUndoLimit; scalar_t__ nUndoStackSize; int /*<<< orphan*/  redo_stack; int /*<<< orphan*/  undo_stack; int /*<<< orphan*/  nTextLimit; scalar_t__ nModifyStep; scalar_t__ nEventMask; void* bCaretAtEnd; int /*<<< orphan*/  hbrBackground; scalar_t__ nTotalWidth; scalar_t__ nLastTotalWidth; scalar_t__ nTotalLength; scalar_t__ nLastTotalLength; int /*<<< orphan*/  style_list; scalar_t__ nAvailWidth; scalar_t__ nZoomDenominator; scalar_t__ nZoomNumerator; int /*<<< orphan*/  pBuffer; scalar_t__ total_rows; int /*<<< orphan*/ * first_marked_para; scalar_t__ exStyleFlags; int /*<<< orphan*/  bEmulateVersion10; int /*<<< orphan*/ * reOle; TYPE_5__ sizeWindow; int /*<<< orphan*/ * hwndParent; int /*<<< orphan*/ * hWnd; } ;
struct TYPE_12__ {int /*<<< orphan*/ * hFont; scalar_t__ nAge; scalar_t__ nRefs; } ;
typedef  int /*<<< orphan*/  SCROLLINFO ;
typedef  TYPE_6__ ME_TextEditor ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  ITextHost ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_WINDOW ; 
 int ECO_AUTOWORDSELECTION ; 
 int ES_AUTOHSCROLL ; 
 int ES_AUTOVSCROLL ; 
 int ES_DISABLENOSCROLL ; 
 int ES_MULTILINE ; 
 int ES_NOHIDESEL ; 
 int ES_NOOLEDRAGDROP ; 
 int ES_READONLY ; 
 int ES_SAVESEL ; 
 int ES_SELECTIONBAR ; 
 int ES_VERTICAL ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int HFONT_CACHE_SIZE ; 
 int /*<<< orphan*/  ITextHost_TxGetPasswordChar (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextHost_TxGetPropertyBits (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ITextHost_TxGetScrollBars (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ITextHost_TxGetSelectionBarWidth (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ME_CheckCharOffsets (TYPE_6__*) ; 
 int /*<<< orphan*/  ME_MakeFirstParagraph (TYPE_6__*) ; 
 int /*<<< orphan*/  ME_MakeText () ; 
 int /*<<< orphan*/  ME_SetCursorToStart (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  OleInitialize (int /*<<< orphan*/ *) ; 
 scalar_t__ SELECTIONBAR_WIDTH ; 
 int /*<<< orphan*/  STACK_SIZE_DEFAULT ; 
 int /*<<< orphan*/  SetRectEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEXT_LIMIT_DEFAULT ; 
 int TM_MULTICODEPAGE ; 
 int TM_MULTILEVELUNDO ; 
 int TM_PLAINTEXT ; 
 int TM_RICHTEXT ; 
 int /*<<< orphan*/  TRUE ; 
 int TXTBIT_AUTOWORDSEL ; 
 int TXTBIT_DISABLEDRAG ; 
 int TXTBIT_HIDESELECTION ; 
 int TXTBIT_MULTILINE ; 
 int TXTBIT_READONLY ; 
 int TXTBIT_RICHTEXT ; 
 int TXTBIT_SAVESELECTION ; 
 int TXTBIT_USEPASSWORD ; 
 int TXTBIT_VERTICAL ; 
 int TXTBIT_WORDWRAP ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stPosition ; 
 int /*<<< orphan*/  umAddToUndo ; 

ME_TextEditor *ME_MakeEditor(ITextHost *texthost, BOOL bEmulateVersion10)
{
  ME_TextEditor *ed = heap_alloc(sizeof(*ed));
  int i;
  DWORD props;
  LONG selbarwidth;

  ed->hWnd = NULL;
  ed->hwndParent = NULL;
  ed->sizeWindow.cx = ed->sizeWindow.cy = 0;
  ed->texthost = texthost;
  ed->reOle = NULL;
  ed->bEmulateVersion10 = bEmulateVersion10;
  ed->styleFlags = 0;
  ed->exStyleFlags = 0;
  ed->first_marked_para = NULL;
  ed->total_rows = 0;
  ITextHost_TxGetPropertyBits(texthost,
                              (TXTBIT_RICHTEXT|TXTBIT_MULTILINE|
                               TXTBIT_READONLY|TXTBIT_USEPASSWORD|
                               TXTBIT_HIDESELECTION|TXTBIT_SAVESELECTION|
                               TXTBIT_AUTOWORDSEL|TXTBIT_VERTICAL|
                               TXTBIT_WORDWRAP|TXTBIT_DISABLEDRAG),
                              &props);
  ITextHost_TxGetScrollBars(texthost, &ed->styleFlags);
  ed->styleFlags &= (WS_VSCROLL|WS_HSCROLL|ES_AUTOVSCROLL|
                     ES_AUTOHSCROLL|ES_DISABLENOSCROLL);
  ed->pBuffer = ME_MakeText();
  ed->nZoomNumerator = ed->nZoomDenominator = 0;
  ed->nAvailWidth = 0; /* wrap to client area */
  list_init( &ed->style_list );
  ME_MakeFirstParagraph(ed);
  /* The four cursors are for:
   * 0 - The position where the caret is shown
   * 1 - The anchored end of the selection (for normal selection)
   * 2 & 3 - The anchored start and end respectively for word, line,
   * or paragraph selection.
   */
  ed->nCursors = 4;
  ed->pCursors = heap_alloc(ed->nCursors * sizeof(*ed->pCursors));
  ME_SetCursorToStart(ed, &ed->pCursors[0]);
  ed->pCursors[1] = ed->pCursors[0];
  ed->pCursors[2] = ed->pCursors[0];
  ed->pCursors[3] = ed->pCursors[1];
  ed->nLastTotalLength = ed->nTotalLength = 0;
  ed->nLastTotalWidth = ed->nTotalWidth = 0;
  ed->nUDArrowX = -1;
  ed->rgbBackColor = -1;
  ed->hbrBackground = GetSysColorBrush(COLOR_WINDOW);
  ed->bCaretAtEnd = FALSE;
  ed->nEventMask = 0;
  ed->nModifyStep = 0;
  ed->nTextLimit = TEXT_LIMIT_DEFAULT;
  list_init( &ed->undo_stack );
  list_init( &ed->redo_stack );
  ed->nUndoStackSize = 0;
  ed->nUndoLimit = STACK_SIZE_DEFAULT;
  ed->nUndoMode = umAddToUndo;
  ed->nParagraphs = 1;
  ed->nLastSelStart = ed->nLastSelEnd = 0;
  ed->pLastSelStartPara = ed->pLastSelEndPara = ed->pCursors[0].pPara;
  ed->bHideSelection = FALSE;
  ed->pfnWordBreak = NULL;
  ed->lpOleCallback = NULL;
  ed->mode = TM_MULTILEVELUNDO | TM_MULTICODEPAGE;
  ed->mode |= (props & TXTBIT_RICHTEXT) ? TM_RICHTEXT : TM_PLAINTEXT;
  ed->AutoURLDetect_bEnable = FALSE;
  ed->bHaveFocus = FALSE;
  ed->bDialogMode = FALSE;
  ed->bMouseCaptured = FALSE;
  for (i=0; i<HFONT_CACHE_SIZE; i++)
  {
    ed->pFontCache[i].nRefs = 0;
    ed->pFontCache[i].nAge = 0;
    ed->pFontCache[i].hFont = NULL;
  }

  ME_CheckCharOffsets(ed);
  SetRectEmpty(&ed->rcFormat);
  ed->bDefaultFormatRect = TRUE;
  ITextHost_TxGetSelectionBarWidth(ed->texthost, &selbarwidth);
  if (selbarwidth) {
    /* FIXME: Convert selbarwidth from HIMETRIC to pixels */
    ed->selofs = SELECTIONBAR_WIDTH;
    ed->styleFlags |= ES_SELECTIONBAR;
  } else {
    ed->selofs = 0;
  }
  ed->nSelectionType = stPosition;

  ed->cPasswordMask = 0;
  if (props & TXTBIT_USEPASSWORD)
    ITextHost_TxGetPasswordChar(texthost, &ed->cPasswordMask);

  if (props & TXTBIT_AUTOWORDSEL)
    ed->styleFlags |= ECO_AUTOWORDSELECTION;
  if (props & TXTBIT_MULTILINE) {
    ed->styleFlags |= ES_MULTILINE;
    ed->bWordWrap = (props & TXTBIT_WORDWRAP) != 0;
  } else {
    ed->bWordWrap = FALSE;
  }
  if (props & TXTBIT_READONLY)
    ed->styleFlags |= ES_READONLY;
  if (!(props & TXTBIT_HIDESELECTION))
    ed->styleFlags |= ES_NOHIDESEL;
  if (props & TXTBIT_SAVESELECTION)
    ed->styleFlags |= ES_SAVESEL;
  if (props & TXTBIT_VERTICAL)
    ed->styleFlags |= ES_VERTICAL;
  if (props & TXTBIT_DISABLEDRAG)
    ed->styleFlags |= ES_NOOLEDRAGDROP;

  ed->notified_cr.cpMin = ed->notified_cr.cpMax = 0;

  /* Default scrollbar information */
  ed->vert_si.cbSize = sizeof(SCROLLINFO);
  ed->vert_si.nMin = 0;
  ed->vert_si.nMax = 0;
  ed->vert_si.nPage = 0;
  ed->vert_si.nPos = 0;

  ed->horz_si.cbSize = sizeof(SCROLLINFO);
  ed->horz_si.nMin = 0;
  ed->horz_si.nMax = 0;
  ed->horz_si.nPage = 0;
  ed->horz_si.nPos = 0;

  ed->wheel_remain = 0;

  list_init( &ed->reobj_list );
  OleInitialize(NULL);

  return ed;
}