#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  sbi ;
typedef  enum SCROLL_HITTEST { ____Placeholder_SCROLL_HITTEST } SCROLL_HITTEST ;
typedef  int UINT ;
struct TYPE_32__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_33__ {TYPE_1__ rcWindow; } ;
struct TYPE_38__ {TYPE_2__ wi; } ;
struct TYPE_37__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_36__ {int SCROLL_trackHitTest; int SCROLL_TrackingPos; int SCROLL_TrackingVal; scalar_t__ SCROLL_TrackingWin; int /*<<< orphan*/  SCROLL_MovingThumb; scalar_t__ SCROLL_TrackingBar; scalar_t__ SCROLL_trackVertical; } ;
struct TYPE_31__ {scalar_t__ top; scalar_t__ left; } ;
struct TYPE_35__ {int cbSize; int* rgstate; int xyThumbTop; TYPE_10__ rcScrollBar; } ;
struct TYPE_34__ {int cbSize; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_3__ SCROLLINFO ;
typedef  TYPE_4__ SCROLLBARINFO ;
typedef  TYPE_5__* PWND_DATA ;
typedef  TYPE_6__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  TYPE_7__ DRAW_CONTEXT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetFocus () ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int /*<<< orphan*/  GetScrollBarInfo (scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  GetScrollInfo (scalar_t__,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  HideCaret (scalar_t__) ; 
 int /*<<< orphan*/  KillSystemTimer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWPARAM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 scalar_t__ SB_CTL ; 
 int /*<<< orphan*/  SB_ENDSCROLL ; 
 int /*<<< orphan*/  SB_LINEDOWN ; 
 int /*<<< orphan*/  SB_LINEUP ; 
 int /*<<< orphan*/  SB_PAGEDOWN ; 
 int /*<<< orphan*/  SB_PAGEUP ; 
 int /*<<< orphan*/  SB_THUMBPOSITION ; 
 int /*<<< orphan*/  SB_THUMBTRACK ; 
#define  SCROLL_BOTTOM_ARROW 137 
#define  SCROLL_BOTTOM_RECT 136 
 TYPE_6__ SCROLL_ClipPos (TYPE_10__*,TYPE_6__) ; 
 int /*<<< orphan*/  SCROLL_DrawArrows (TYPE_7__*,TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCROLL_DrawInterior (TYPE_7__*,TYPE_4__*,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  SCROLL_DrawMovingThumb (TYPE_5__*,TYPE_7__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  SCROLL_FIRST_DELAY ; 
 void* SCROLL_GetThumbVal (TYPE_3__*,TYPE_10__*,scalar_t__,int) ; 
 int SCROLL_HitTest (scalar_t__,TYPE_4__*,scalar_t__,TYPE_6__,int /*<<< orphan*/ ) ; 
 scalar_t__ SCROLL_IsVertical (scalar_t__,scalar_t__) ; 
#define  SCROLL_NOWHERE 135 
 int /*<<< orphan*/  SCROLL_PtInRectEx (TYPE_10__*,TYPE_6__,scalar_t__) ; 
 int /*<<< orphan*/  SCROLL_REPEAT_DELAY ; 
#define  SCROLL_THUMB 134 
 int /*<<< orphan*/  SCROLL_TIMER ; 
#define  SCROLL_TOP_ARROW 133 
#define  SCROLL_TOP_RECT 132 
 int /*<<< orphan*/  SCROLL_getObjectId (scalar_t__) ; 
 int /*<<< orphan*/  SIF_ALL ; 
 int STATE_SYSTEM_UNAVAILABLE ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCapture (scalar_t__) ; 
 int /*<<< orphan*/  SetSystemTimer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowCaret (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ThemeCleanupDrawContext (TYPE_7__*) ; 
 int /*<<< orphan*/  ThemeInitDrawContext (TYPE_7__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_HSCROLL ; 
#define  WM_LBUTTONDOWN 131 
#define  WM_LBUTTONUP 130 
#define  WM_MOUSEMOVE 129 
#define  WM_SYSTIMER 128 
 int /*<<< orphan*/  WM_VSCROLL ; 

__attribute__((used)) static void 
SCROLL_HandleScrollEvent(PWND_DATA pwndData, HWND hwnd, INT nBar, UINT msg, POINT pt)
{
      /* Previous mouse position for timer events */
    static POINT prevPt;
      /* Thumb position when tracking started. */
    static UINT trackThumbPos;
      /* Position in the scroll-bar of the last button-down event. */
    static INT lastClickPos;
      /* Position in the scroll-bar of the last mouse event. */
    static INT lastMousePos;

    enum SCROLL_HITTEST hittest;
    HWND hwndOwner, hwndCtl;
    BOOL vertical;
    SCROLLINFO si;
    SCROLLBARINFO sbi;
    DRAW_CONTEXT context;

    si.cbSize = sizeof(si);
    sbi.cbSize = sizeof(sbi);
    si.fMask = SIF_ALL;
    GetScrollInfo(hwnd, nBar, &si);
    GetScrollBarInfo(hwnd, SCROLL_getObjectId(nBar), &sbi);
    vertical = SCROLL_IsVertical(hwnd, nBar);
    if(sbi.rgstate[SCROLL_TOP_ARROW] & STATE_SYSTEM_UNAVAILABLE  && 
       sbi.rgstate[SCROLL_BOTTOM_ARROW] & STATE_SYSTEM_UNAVAILABLE  )
    {
        return;
    }

    if ((pwndData->SCROLL_trackHitTest == SCROLL_NOWHERE) && (msg != WM_LBUTTONDOWN))
		  return;
    
    ThemeInitDrawContext(&context, hwnd, 0);

    /* The scrollbar rect is in screen coordinates */
    OffsetRect(&sbi.rcScrollBar, -context.wi.rcWindow.left, -context.wi.rcWindow.top);

    hwndOwner = (nBar == SB_CTL) ? GetParent(hwnd) : hwnd;
    hwndCtl   = (nBar == SB_CTL) ? hwnd : 0;

    switch(msg)
    {
      case WM_LBUTTONDOWN:  /* Initialise mouse tracking */
          HideCaret(hwnd);  /* hide caret while holding down LBUTTON */
          pwndData->SCROLL_trackVertical = vertical;
          pwndData->SCROLL_trackHitTest  = hittest = SCROLL_HitTest( hwnd, &sbi, vertical, pt, FALSE );
          lastClickPos  = vertical ? (pt.y - sbi.rcScrollBar.top) : (pt.x - sbi.rcScrollBar.left);
          lastMousePos  = lastClickPos;
          trackThumbPos = sbi.xyThumbTop;
          prevPt = pt;
          SetCapture( hwnd );
          break;

      case WM_MOUSEMOVE:
          hittest = SCROLL_HitTest( hwnd, &sbi, vertical, pt, TRUE );
          prevPt = pt;
          break;

      case WM_LBUTTONUP:
          hittest = SCROLL_NOWHERE;
          ReleaseCapture();
          /* if scrollbar has focus, show back caret */
          if (hwnd==GetFocus()) 
              ShowCaret(hwnd);
          break;

      case WM_SYSTIMER:
          pt = prevPt;
          hittest = SCROLL_HitTest( hwnd, &sbi, vertical, pt, FALSE );
          break;

      default:
          return;  /* Should never happen */
    }

    //TRACE("Event: hwnd=%p bar=%d msg=%s pt=%d,%d hit=%d\n",
    //      hwnd, nBar, SPY_GetMsgName(msg,hwnd), pt.x, pt.y, hittest );

    switch(pwndData->SCROLL_trackHitTest)
    {
    case SCROLL_NOWHERE:  /* No tracking in progress */
        break;

    case SCROLL_TOP_ARROW:
        if (hittest == pwndData->SCROLL_trackHitTest)
        {
            SCROLL_DrawArrows( &context, &sbi, vertical, pwndData->SCROLL_trackHitTest, 0 );
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_SYSTIMER))
            {
                SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                                SB_LINEUP, (LPARAM)hwndCtl );
	        }

        SetSystemTimer( hwnd, SCROLL_TIMER, (msg == WM_LBUTTONDOWN) ?
                            SCROLL_FIRST_DELAY : SCROLL_REPEAT_DELAY, NULL );
        }
        else
        {
            SCROLL_DrawArrows( &context, &sbi, vertical, 0, 0 );
            KillSystemTimer( hwnd, SCROLL_TIMER );
        }

        break;

    case SCROLL_TOP_RECT:
        SCROLL_DrawInterior( &context, &sbi, sbi.xyThumbTop, vertical, pwndData->SCROLL_trackHitTest, 0);
        if (hittest == pwndData->SCROLL_trackHitTest)
        {
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_SYSTIMER))
            {
                SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                                SB_PAGEUP, (LPARAM)hwndCtl );
            }
            SetSystemTimer( hwnd, SCROLL_TIMER, (msg == WM_LBUTTONDOWN) ?
                              SCROLL_FIRST_DELAY : SCROLL_REPEAT_DELAY, NULL );
        }
        else KillSystemTimer( hwnd, SCROLL_TIMER );
        break;

    case SCROLL_THUMB:
        if (msg == WM_LBUTTONDOWN)
        {
            pwndData->SCROLL_TrackingWin = hwnd;
            pwndData->SCROLL_TrackingBar = nBar;
            pwndData->SCROLL_TrackingPos = trackThumbPos + lastMousePos - lastClickPos;
            pwndData->SCROLL_TrackingVal = SCROLL_GetThumbVal( &si, &sbi.rcScrollBar, 
                                                     vertical, pwndData->SCROLL_TrackingPos );
	        if (!pwndData->SCROLL_MovingThumb)
		        SCROLL_DrawMovingThumb(pwndData, &context, &sbi, vertical);
        }
        else if (msg == WM_LBUTTONUP)
        {
	        if (pwndData->SCROLL_MovingThumb)
		        SCROLL_DrawMovingThumb(pwndData, &context, &sbi, vertical);

            SCROLL_DrawInterior(  &context, &sbi, sbi.xyThumbTop, vertical, 0, pwndData->SCROLL_trackHitTest );
        }
        else  /* WM_MOUSEMOVE */
        {
            INT pos;

            if (!SCROLL_PtInRectEx( &sbi.rcScrollBar, pt, vertical )) 
                pos = lastClickPos;
            else
            {
                pt = SCROLL_ClipPos( &sbi.rcScrollBar, pt );
                pos = vertical ? (pt.y - sbi.rcScrollBar.top) : (pt.x - sbi.rcScrollBar.left);
            }
            if ( (pos != lastMousePos) || (!pwndData->SCROLL_MovingThumb) )
            {
                if (pwndData->SCROLL_MovingThumb)
                    SCROLL_DrawMovingThumb(pwndData, &context, &sbi, vertical);
                lastMousePos = pos;
                pwndData->SCROLL_TrackingPos = trackThumbPos + pos - lastClickPos;
                pwndData->SCROLL_TrackingVal = SCROLL_GetThumbVal( &si, &sbi.rcScrollBar,
                                                         vertical,
                                                         pwndData->SCROLL_TrackingPos );
                SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                                MAKEWPARAM( SB_THUMBTRACK, pwndData->SCROLL_TrackingVal),
                                (LPARAM)hwndCtl );
                if (!pwndData->SCROLL_MovingThumb)
                    SCROLL_DrawMovingThumb(pwndData, &context, &sbi, vertical);
            }
        }
        break;

    case SCROLL_BOTTOM_RECT:
        if (hittest == pwndData->SCROLL_trackHitTest)
        {
            SCROLL_DrawInterior(  &context, &sbi, sbi.xyThumbTop, vertical, pwndData->SCROLL_trackHitTest, 0 );
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_SYSTIMER))
            {
                SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                                SB_PAGEDOWN, (LPARAM)hwndCtl );
            }
            SetSystemTimer( hwnd, SCROLL_TIMER, (msg == WM_LBUTTONDOWN) ?
                              SCROLL_FIRST_DELAY : SCROLL_REPEAT_DELAY, NULL );
        }
        else
        {
            SCROLL_DrawInterior(  &context, &sbi, sbi.xyThumbTop, vertical, 0, 0 );
            KillSystemTimer( hwnd, SCROLL_TIMER );
        }
        break;

    case SCROLL_BOTTOM_ARROW:
        if (hittest == pwndData->SCROLL_trackHitTest)
        {
            SCROLL_DrawArrows(  &context, &sbi, vertical, pwndData->SCROLL_trackHitTest, 0 );
            if ((msg == WM_LBUTTONDOWN) || (msg == WM_SYSTIMER))
            {
                SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                                SB_LINEDOWN, (LPARAM)hwndCtl );
	        }

        SetSystemTimer( hwnd, SCROLL_TIMER, (msg == WM_LBUTTONDOWN) ?
                            SCROLL_FIRST_DELAY : SCROLL_REPEAT_DELAY, NULL );
        }
        else
        {
            SCROLL_DrawArrows(  &context, &sbi, vertical, 0, 0 );
            KillSystemTimer( hwnd, SCROLL_TIMER );
        }
        break;
    }

    if (msg == WM_LBUTTONDOWN)
    {

        if (hittest == SCROLL_THUMB)
        {
            UINT val = SCROLL_GetThumbVal( &si, &sbi.rcScrollBar, vertical,
                                 trackThumbPos + lastMousePos - lastClickPos );
            SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                            MAKEWPARAM( SB_THUMBTRACK, val ), (LPARAM)hwndCtl );
        }
    }

    if (msg == WM_LBUTTONUP)
    {
        hittest = pwndData->SCROLL_trackHitTest;
        pwndData->SCROLL_trackHitTest = SCROLL_NOWHERE;  /* Terminate tracking */

        if (hittest == SCROLL_THUMB)
        {
            UINT val = SCROLL_GetThumbVal( &si, &sbi.rcScrollBar, vertical,
                                 trackThumbPos + lastMousePos - lastClickPos );
            SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                            MAKEWPARAM( SB_THUMBPOSITION, val ), (LPARAM)hwndCtl );
        }
        /* SB_ENDSCROLL doesn't report thumb position */
        SendMessageW( hwndOwner, vertical ? WM_VSCROLL : WM_HSCROLL,
                          SB_ENDSCROLL, (LPARAM)hwndCtl );

        /* Terminate tracking */
        pwndData->SCROLL_TrackingWin = 0;
    }

    ThemeCleanupDrawContext(&context);
}