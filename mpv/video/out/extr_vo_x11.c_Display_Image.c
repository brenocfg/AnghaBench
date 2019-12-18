#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vo {TYPE_1__* x11; int /*<<< orphan*/  dheight; int /*<<< orphan*/  dwidth; } ;
struct TYPE_4__ {int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
struct priv {size_t current_buf; int reset_view; int /*<<< orphan*/  dst_h; int /*<<< orphan*/  dst_w; TYPE_2__ dst; int /*<<< orphan*/  gc; scalar_t__ Shmem_Flag; int /*<<< orphan*/ ** myximage; struct vo* vo; } ;
typedef  int /*<<< orphan*/  XImage ;
struct TYPE_3__ {int /*<<< orphan*/  window; int /*<<< orphan*/  display; int /*<<< orphan*/  ShmCompletionWaitCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XFillRectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XShmPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Display_Image(struct priv *p, XImage *myximage)
{
    struct vo *vo = p->vo;

    XImage *x_image = p->myximage[p->current_buf];

    if (p->reset_view) {
        XFillRectangle(vo->x11->display, vo->x11->window, p->gc, 0, 0, vo->dwidth, vo->dheight);
        p->reset_view = false;
    }

    if (p->Shmem_Flag) {
        XShmPutImage(vo->x11->display, vo->x11->window, p->gc, x_image,
                     0, 0, p->dst.x0, p->dst.y0, p->dst_w, p->dst_h,
                     True);
        vo->x11->ShmCompletionWaitCount++;
    } else {
        XPutImage(vo->x11->display, vo->x11->window, p->gc, x_image,
                  0, 0, p->dst.x0, p->dst.y0, p->dst_w, p->dst_h);
    }
}