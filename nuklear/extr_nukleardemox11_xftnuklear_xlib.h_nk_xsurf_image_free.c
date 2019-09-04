#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* ptr; } ;
struct nk_image {TYPE_1__ handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  dpy; } ;
typedef  TYPE_2__ XSurface ;
struct TYPE_8__ {int /*<<< orphan*/  clipMaskGC; int /*<<< orphan*/  clipMask; int /*<<< orphan*/  ximage; } ;
typedef  TYPE_3__ XImageWithAlpha ;
struct TYPE_9__ {TYPE_2__* surf; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDestroyImage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_4__ xlib ; 

void
nk_xsurf_image_free(struct nk_image* image)
{
    XSurface *surf = xlib.surf;
    XImageWithAlpha *aimage = image->handle.ptr;
    if (!aimage) return;
    XDestroyImage(aimage->ximage);
    XFreePixmap(surf->dpy, aimage->clipMask);
    XFreeGC(surf->dpy, aimage->clipMaskGC);
    free(aimage);
}