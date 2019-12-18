#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nk_image {void* w; void* h; } ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  GpImage ;

/* Variables and functions */
 int /*<<< orphan*/  GdipGetImageHeight (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  GdipGetImageWidth (int /*<<< orphan*/ *,void**) ; 
 struct nk_image nk_image_ptr (void*) ; 

__attribute__((used)) static struct nk_image
nk_gdip_image_to_nk(GpImage *image) {
    struct nk_image img;
    UINT uwidth, uheight;
    img = nk_image_ptr( (void*)image );
    GdipGetImageHeight(image, &uheight);
    GdipGetImageWidth(image, &uwidth);
    img.h = uheight;
    img.w = uwidth;
    return img;
}