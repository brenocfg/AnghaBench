#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xvctx {int cfg_xv_adaptor; unsigned int adaptors; scalar_t__ xv_port; int /*<<< orphan*/  formats; int /*<<< orphan*/  fo; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; TYPE_1__* ai; } ;
struct vo_x11_state {int /*<<< orphan*/  display; } ;
struct vo {struct vo_x11_state* x11; struct xvctx* priv; } ;
typedef  scalar_t__ XvPortID ;
struct TYPE_2__ {int type; scalar_t__ base_id; scalar_t__ num_ports; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_WARN (struct vo*,char*,...) ; 
 scalar_t__ Success ; 
 scalar_t__ XvGrabPort (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int XvImageMask ; 
 int XvInputMask ; 
 int /*<<< orphan*/  XvListImageFormats (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ XvQueryAdaptors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,TYPE_1__**) ; 
 scalar_t__ XvQueryExtension (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  uninit (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_create_vo_window (struct vo*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vo_x11_init (struct vo*) ; 
 int /*<<< orphan*/  xv_enable_vsync (struct vo*) ; 
 int /*<<< orphan*/  xv_get_max_img_dim (struct vo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xv_init_colorkey (struct vo*) ; 

__attribute__((used)) static int preinit(struct vo *vo)
{
    XvPortID xv_p;
    int busy_ports = 0;
    unsigned int i;
    struct xvctx *ctx = vo->priv;
    int xv_adaptor = ctx->cfg_xv_adaptor;

    if (!vo_x11_init(vo))
        return -1;

    if (!vo_x11_create_vo_window(vo, NULL, "xv"))
        goto error;

    struct vo_x11_state *x11 = vo->x11;

    /* check for Xvideo extension */
    unsigned int ver, rel, req, ev, err;
    if (Success != XvQueryExtension(x11->display, &ver, &rel, &req, &ev, &err)) {
        MP_ERR(vo, "Xv not supported by this X11 version/driver\n");
        goto error;
    }

    /* check for Xvideo support */
    if (Success !=
        XvQueryAdaptors(x11->display, DefaultRootWindow(x11->display),
                        &ctx->adaptors, &ctx->ai)) {
        MP_ERR(vo, "XvQueryAdaptors failed.\n");
        goto error;
    }

    /* check adaptors */
    if (ctx->xv_port) {
        int port_found;

        for (port_found = 0, i = 0; !port_found && i < ctx->adaptors; i++) {
            if ((ctx->ai[i].type & XvInputMask)
                && (ctx->ai[i].type & XvImageMask)) {
                for (xv_p = ctx->ai[i].base_id;
                     xv_p < ctx->ai[i].base_id + ctx->ai[i].num_ports;
                     ++xv_p) {
                    if (xv_p == ctx->xv_port) {
                        port_found = 1;
                        break;
                    }
                }
            }
        }
        if (port_found) {
            if (XvGrabPort(x11->display, ctx->xv_port, CurrentTime))
                ctx->xv_port = 0;
        } else {
            MP_WARN(vo, "Invalid port parameter, overriding with port 0.\n");
            ctx->xv_port = 0;
        }
    }

    for (i = 0; i < ctx->adaptors && ctx->xv_port == 0; i++) {
        /* check if adaptor number has been specified */
        if (xv_adaptor != -1 && xv_adaptor != i)
            continue;

        if ((ctx->ai[i].type & XvInputMask) && (ctx->ai[i].type & XvImageMask)) {
            for (xv_p = ctx->ai[i].base_id;
                 xv_p < ctx->ai[i].base_id + ctx->ai[i].num_ports; ++xv_p)
                if (!XvGrabPort(x11->display, xv_p, CurrentTime)) {
                    ctx->xv_port = xv_p;
                    MP_VERBOSE(vo, "Using Xv Adapter #%d (%s)\n",
                               i, ctx->ai[i].name);
                    break;
                } else {
                    MP_WARN(vo, "Could not grab port %i.\n", (int) xv_p);
                    ++busy_ports;
                }
        }
    }
    if (!ctx->xv_port) {
        if (busy_ports)
            MP_ERR(vo, "Xvideo ports busy.\n");
        else
            MP_ERR(vo, "No Xvideo support found.\n");
        goto error;
    }

    if (!xv_init_colorkey(vo)) {
        goto error;             // bail out, colorkey setup failed
    }
    xv_enable_vsync(vo);
    xv_get_max_img_dim(vo, &ctx->max_width, &ctx->max_height);

    ctx->fo = XvListImageFormats(x11->display, ctx->xv_port,
                                 (int *) &ctx->formats);

    MP_WARN(vo, "Warning: this legacy VO has bad quality and performance, "
                "and will in particular result in blurry OSD and subtitles. "
                "You should fix your graphics drivers, or not force the xv VO.\n");
    return 0;

  error:
    uninit(vo);                 // free resources
    return -1;
}