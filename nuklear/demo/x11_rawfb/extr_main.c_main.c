#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rawfb_context {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  rawfb_pl ;
struct TYPE_7__ {int event_mask; int /*<<< orphan*/  colormap; } ;
struct TYPE_6__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_5__ {unsigned int width; unsigned int height; int /*<<< orphan*/  dpy; int /*<<< orphan*/  win; int /*<<< orphan*/  cmap; int /*<<< orphan*/  screen; TYPE_4__ swa; int /*<<< orphan*/  vis; TYPE_3__ attr; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ XWindow ;
typedef  int /*<<< orphan*/  XEvent ;

/* Variables and functions */
 int /*<<< orphan*/  AllocNone ; 
 int Button1MotionMask ; 
 int Button3MotionMask ; 
 int Button4MotionMask ; 
 int Button5MotionMask ; 
 int ButtonMotionMask ; 
 int ButtonPress ; 
 int ButtonReleaseMask ; 
 int CWColormap ; 
 int CWEventMask ; 
 long DTIME ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int EnterWindowMask ; 
 int ExposureMask ; 
 int /*<<< orphan*/  InputOutput ; 
 int KeyPressMask ; 
 int KeyReleaseMask ; 
 int KeymapStateMask ; 
 int LeaveWindowMask ; 
 int NK_WINDOW_BORDER ; 
 int NK_WINDOW_CLOSABLE ; 
 int NK_WINDOW_MINIMIZABLE ; 
 int NK_WINDOW_MOVABLE ; 
 int NK_WINDOW_TITLE ; 
 int PointerMotionMask ; 
 int /*<<< orphan*/  WINDOW_HEIGHT ; 
 int /*<<< orphan*/  WINDOW_WIDTH ; 
 scalar_t__ XCheckWindowEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XClearWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*) ; 
 int /*<<< orphan*/  XDefaultDepth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefaultVisual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XFilterEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XStoreName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XUnmapWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nk_begin (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nk_button_label (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nk_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_input_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_input_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nk_layout_row_static (int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ nk_option_label (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  nk_property_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,int,int,int) ; 
 struct rawfb_context* nk_rawfb_init (void*,unsigned char*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_rawfb_render (struct rawfb_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nk_rawfb_shutdown (struct rawfb_context*) ; 
 int /*<<< orphan*/  nk_rect (int,int,int,int) ; 
 int /*<<< orphan*/  nk_rgb (int,int,int) ; 
 scalar_t__ nk_window_is_closed (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nk_xlib_handle_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rawfb_context*) ; 
 int nk_xlib_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nk_xlib_render (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_xlib_shutdown () ; 
 int /*<<< orphan*/  node_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  overview (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep_for (long) ; 
 int /*<<< orphan*/  stdout ; 
 long timestamp () ; 

int
main(void)
{
    long dt;
    long started;
    int running = 1;
    int status;
    XWindow xw;
    struct rawfb_context *rawfb;
    void *fb = NULL;
    rawfb_pl pl;
    unsigned char tex_scratch[512 * 512];

    /* X11 */
    memset(&xw, 0, sizeof xw);
    xw.dpy = XOpenDisplay(NULL);
    if (!xw.dpy) die("Could not open a display; perhaps $DISPLAY is not set?");

    xw.root = DefaultRootWindow(xw.dpy);
    xw.screen = XDefaultScreen(xw.dpy);
    xw.vis = XDefaultVisual(xw.dpy, xw.screen);
    xw.cmap = XCreateColormap(xw.dpy,xw.root,xw.vis,AllocNone);
    xw.swa.colormap = xw.cmap;
    xw.swa.event_mask =
        ExposureMask | KeyPressMask | KeyReleaseMask |
        ButtonPress | ButtonReleaseMask| ButtonMotionMask |
        Button1MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask|
        PointerMotionMask | KeymapStateMask | EnterWindowMask | LeaveWindowMask;
    xw.win = XCreateWindow(xw.dpy, xw.root, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0,
        XDefaultDepth(xw.dpy, xw.screen), InputOutput,
        xw.vis, CWEventMask | CWColormap, &xw.swa);

    XStoreName(xw.dpy, xw.win, "X11");
    XMapWindow(xw.dpy, xw.win);
    XGetWindowAttributes(xw.dpy, xw.win, &xw.attr);
    xw.width = (unsigned int)xw.attr.width;
    xw.height = (unsigned int)xw.attr.height;

    /* Framebuffer emulator */
    status = nk_xlib_init(xw.dpy, xw.vis, xw.screen, xw.win, xw.width, xw.height, &fb, &pl);
    if (!status || !fb)
        return 0;

    /* GUI */
    rawfb = nk_rawfb_init(fb, tex_scratch, xw.width, xw.height, xw.width * 4, pl);
    if (!rawfb) running = 0;

    #ifdef INCLUDE_STYLE
    /*set_style(&rawfb->ctx, THEME_WHITE);*/
    /*set_style(&rawfb->ctx, THEME_RED);*/
    /*set_style(&rawfb->ctx, THEME_BLUE);*/
    /*set_style(&rawfb->ctx, THEME_DARK);*/
    #endif

    while (running) {
        /* Input */
        XEvent evt;
        started = timestamp();
        nk_input_begin(&rawfb->ctx);
        while (XCheckWindowEvent(xw.dpy, xw.win, xw.swa.event_mask, &evt)) {
            if (XFilterEvent(&evt, xw.win)) continue;
            nk_xlib_handle_event(xw.dpy, xw.screen, xw.win, &evt, rawfb);
        }
        nk_input_end(&rawfb->ctx);

        /* GUI */
        if (nk_begin(&rawfb->ctx, "Demo", nk_rect(50, 50, 200, 200),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|
            NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE)) {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(&rawfb->ctx, 30, 80, 1);
            if (nk_button_label(&rawfb->ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(&rawfb->ctx, 30, 2);
            if (nk_option_label(&rawfb->ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(&rawfb->ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(&rawfb->ctx, 25, 1);
            nk_property_int(&rawfb->ctx, "Compression:", 0, &property, 100, 10, 1);
        }
        nk_end(&rawfb->ctx);
        if (nk_window_is_closed(&rawfb->ctx, "Demo")) break;

        /* -------------- EXAMPLES ---------------- */
        #ifdef INCLUDE_CALCULATOR
          calculator(&rawfb->ctx);
        #endif
        #ifdef INCLUDE_OVERVIEW
          overview(&rawfb->ctx);
        #endif
        #ifdef INCLUDE_NODE_EDITOR
          node_editor(&rawfb->ctx);
        #endif
        /* ----------------------------------------- */

        /* Draw framebuffer */
        nk_rawfb_render(rawfb, nk_rgb(30,30,30), 1);

        /* Emulate framebuffer */
        XClearWindow(xw.dpy, xw.win);
        nk_xlib_render(xw.win);
        XFlush(xw.dpy);

        /* Timing */
        dt = timestamp() - started;
        if (dt < DTIME)
            sleep_for(DTIME - dt);
    }

    nk_rawfb_shutdown(rawfb);
    nk_xlib_shutdown();
    XUnmapWindow(xw.dpy, xw.win);
    XFreeColormap(xw.dpy, xw.cmap);
    XDestroyWindow(xw.dpy, xw.win);
    XCloseDisplay(xw.dpy);
    return 0;
}