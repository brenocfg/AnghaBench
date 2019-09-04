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
struct TYPE_2__ {int method; int source; } ;
struct xvctx {int /*<<< orphan*/  xv_colorkey; TYPE_1__ xv_ck_info; } ;
struct vo {struct xvctx* priv; } ;

/* Variables and functions */
#define  CK_METHOD_AUTOPAINT 134 
#define  CK_METHOD_BACKGROUND 133 
#define  CK_METHOD_MANUALFILL 132 
#define  CK_METHOD_NONE 131 
#define  CK_SRC_CUR 130 
#define  CK_SRC_SET 129 
#define  CK_SRC_USE 128 
 int /*<<< orphan*/  MP_VERBOSE (struct vo*,char*,...) ; 

__attribute__((used)) static void xv_print_ck_info(struct vo *vo)
{
    struct xvctx *xv = vo->priv;

    switch (xv->xv_ck_info.method) {
    case CK_METHOD_NONE:
        MP_VERBOSE(vo, "Drawing no colorkey.\n");
        return;
    case CK_METHOD_AUTOPAINT:
        MP_VERBOSE(vo, "Colorkey is drawn by Xv.\n");
        break;
    case CK_METHOD_MANUALFILL:
        MP_VERBOSE(vo, "Drawing colorkey manually.\n");
        break;
    case CK_METHOD_BACKGROUND:
        MP_VERBOSE(vo, "Colorkey is drawn as window background.\n");
        break;
    }

    switch (xv->xv_ck_info.source) {
    case CK_SRC_CUR:
        MP_VERBOSE(vo, "Using colorkey from Xv (0x%06lx).\n", xv->xv_colorkey);
        break;
    case CK_SRC_USE:
        if (xv->xv_ck_info.method == CK_METHOD_AUTOPAINT) {
            MP_VERBOSE(vo, "Ignoring colorkey from mpv (0x%06lx).\n",
                       xv->xv_colorkey);
        } else {
            MP_VERBOSE(vo, "Using colorkey from mpv (0x%06lx). Use -colorkey to change.\n",
                       xv->xv_colorkey);
        }
        break;
    case CK_SRC_SET:
        MP_VERBOSE(vo, "Setting and using colorkey from mpv (0x%06lx)."
                   " Use -colorkey to change.\n", xv->xv_colorkey);
        break;
    }
}