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
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
struct nk_image {TYPE_1__ handle; } ;
struct nk_color {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  GpImage ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDrawImageRectI (int /*<<< orphan*/ ,int /*<<< orphan*/ *,short,short,unsigned short,unsigned short) ; 
 TYPE_2__ gdip ; 

__attribute__((used)) static void
nk_gdip_draw_image(short x, short y, unsigned short w, unsigned short h,
    struct nk_image img, struct nk_color col)
{
    GpImage *image = img.handle.ptr;
    GdipDrawImageRectI(gdip.memory, image, x, y, w, h);
}