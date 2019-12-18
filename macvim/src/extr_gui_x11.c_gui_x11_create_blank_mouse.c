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
typedef  int /*<<< orphan*/  XGCValues ;
typedef  int /*<<< orphan*/  XColor ;
struct TYPE_2__ {int /*<<< orphan*/  norm_pixel; int /*<<< orphan*/  dpy; int /*<<< orphan*/  wid; } ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  GC ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  XCreateGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCreatePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  XCreatePixmapCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDrawPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ gui ; 

__attribute__((used)) static Cursor
gui_x11_create_blank_mouse()
{
    Pixmap blank_pixmap = XCreatePixmap(gui.dpy, gui.wid, 1, 1, 1);
    GC gc = XCreateGC(gui.dpy, blank_pixmap, (unsigned long)0, (XGCValues*)0);
    XDrawPoint(gui.dpy, blank_pixmap, gc, 0, 0);
    XFreeGC(gui.dpy, gc);
    return XCreatePixmapCursor(gui.dpy, blank_pixmap, blank_pixmap,
	    (XColor*)&gui.norm_pixel, (XColor*)&gui.norm_pixel, 0, 0);
}