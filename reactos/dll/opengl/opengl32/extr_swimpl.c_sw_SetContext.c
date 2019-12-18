#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  hdc; int /*<<< orphan*/  hwnd; } ;
struct wgl_dc_data {int flags; TYPE_1__ owner; struct sw_framebuffer* sw_data; } ;
struct sw_framebuffer {int /*<<< orphan*/  gl_buffer; TYPE_2__* gl_visual; } ;
struct sw_context {TYPE_7__* gl_ctx; int /*<<< orphan*/  hook; } ;
typedef  int /*<<< orphan*/  bm ;
typedef  int UINT ;
struct TYPE_15__ {scalar_t__ X; scalar_t__ Y; scalar_t__ Width; scalar_t__ Height; } ;
struct TYPE_19__ {TYPE_3__ Viewport; } ;
struct TYPE_18__ {int /*<<< orphan*/  glDispatchTable; } ;
struct TYPE_17__ {int bmWidth; int bmHeight; } ;
struct TYPE_16__ {int right; int left; int bottom; int top; } ;
struct TYPE_14__ {scalar_t__ DBflag; } ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  scalar_t__ DHGLRC ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_5__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 scalar_t__ GetObject (int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int /*<<< orphan*/  IntSetCurrentDispatchTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_BITMAP ; 
 int /*<<< orphan*/  SetWindowsHookEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WGL_DC_OBJ_DC ; 
 int /*<<< orphan*/  WH_CALLWNDPROC ; 
 int /*<<< orphan*/  gl_ResizeBuffersMESA (TYPE_7__*) ; 
 int /*<<< orphan*/  gl_Viewport (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gl_make_current (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_DD_pointers (TYPE_7__*) ; 
 TYPE_6__ sw_api_table ; 
 int /*<<< orphan*/  sw_call_window_proc ; 

BOOL sw_SetContext(struct wgl_dc_data* dc_data, DHGLRC dhglrc)
{
    struct sw_context* sw_ctx = (struct sw_context*)dhglrc;
    struct sw_framebuffer* fb = dc_data->sw_data;
    UINT width, height;
    
    /* Get framebuffer size */
    if(dc_data->flags & WGL_DC_OBJ_DC)
    {
        HWND hwnd = dc_data->owner.hwnd;
        RECT client_rect;
        if(!hwnd)
        {
            ERR("Physical DC without a window!\n");
            return FALSE;
        }
        if(!GetClientRect(hwnd, &client_rect))
        {
            ERR("GetClientRect failed!\n");
            return FALSE;
        }

        /* This is a physical DC. Setup the hook */
        sw_ctx->hook = SetWindowsHookEx(WH_CALLWNDPROC,
                            sw_call_window_proc,
                            NULL,
                            GetCurrentThreadId());

        /* Calculate width & height */
        width  = client_rect.right  - client_rect.left;
        height = client_rect.bottom - client_rect.top;
    }
    else /* OBJ_MEMDC */
    {
        BITMAP bm;
        HBITMAP hbmp;
        HDC hdc = dc_data->owner.hdc;
        
        if(fb->gl_visual->DBflag)
        {
            ERR("Memory DC called with a double buffered format.\n");
            return FALSE;
        }
        
        hbmp = GetCurrentObject( hdc, OBJ_BITMAP );
        if(!hbmp)
        {
            ERR("No Bitmap!\n");
            return FALSE;
        }
        if(GetObject(hbmp, sizeof(bm), &bm) == 0)
        {
            ERR("GetObject failed!\n");
            return FALSE;
        }
        width = bm.bmWidth;
        height = bm.bmHeight;
    }
    
    if(!width) width = 1;
    if(!height) height = 1;
    
    /* Also make the mesa context current to mesa */
    gl_make_current(sw_ctx->gl_ctx, fb->gl_buffer);

    /* Setup our functions */
    setup_DD_pointers(sw_ctx->gl_ctx);

    /* Set the viewport if this is the first time we initialize this context */
    if(sw_ctx->gl_ctx->Viewport.X == 0 &&
       sw_ctx->gl_ctx->Viewport.Y == 0 &&
       sw_ctx->gl_ctx->Viewport.Width == 0 &&
       sw_ctx->gl_ctx->Viewport.Height == 0)
    {
        gl_Viewport(sw_ctx->gl_ctx, 0, 0, width, height);
    }

    /* update the framebuffer size */
    gl_ResizeBuffersMESA(sw_ctx->gl_ctx);

    /* Use our API table */
    IntSetCurrentDispatchTable(&sw_api_table.glDispatchTable);

   /* We're good */
   return TRUE;
}