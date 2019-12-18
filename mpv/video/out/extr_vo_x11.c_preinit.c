#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vo_x11_state {int /*<<< orphan*/  window; int /*<<< orphan*/  display; int /*<<< orphan*/  screen; int /*<<< orphan*/  rootwin; } ;
struct vo {struct vo_x11_state* x11; int /*<<< orphan*/  global; int /*<<< orphan*/  log; struct priv* priv; } ;
struct TYPE_8__ {scalar_t__ visualid; } ;
struct priv {int /*<<< orphan*/  gc; TYPE_2__ vinfo; int /*<<< orphan*/  depth; TYPE_3__* sws; struct vo* vo; } ;
struct TYPE_7__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ XWindowAttributes ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,int) ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*) ; 
 int /*<<< orphan*/  TrueColor ; 
 int /*<<< orphan*/  XCreateGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  XMatchVisualInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_3__* mp_sws_alloc (struct vo*) ; 
 int /*<<< orphan*/  mp_sws_enable_cmdline_opts (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uninit (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_create_vo_window (struct vo*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vo_x11_init (struct vo*) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    struct priv *p = vo->priv;
    p->vo = vo;
    p->sws = mp_sws_alloc(vo);
    p->sws->log = vo->log;
    mp_sws_enable_cmdline_opts(p->sws, vo->global);

    if (!vo_x11_init(vo))
        goto error;
    struct vo_x11_state *x11 = vo->x11;

    XWindowAttributes attribs;
    XGetWindowAttributes(x11->display, x11->rootwin, &attribs);
    p->depth = attribs.depth;

    if (!XMatchVisualInfo(x11->display, x11->screen, p->depth,
                          TrueColor, &p->vinfo))
        goto error;

    MP_VERBOSE(vo, "selected visual: %d\n", (int)p->vinfo.visualid);

    if (!vo_x11_create_vo_window(vo, &p->vinfo, "x11"))
        goto error;

    p->gc = XCreateGC(x11->display, x11->window, 0, NULL);
    MP_WARN(vo, "Warning: this legacy VO has bad performance. Consider fixing "
                "your graphics drivers, or not forcing the x11 VO.\n");
    return 0;

error:
    uninit(vo);
    return -1;
}