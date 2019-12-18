#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  image_id; } ;
struct va_surface {scalar_t__ is_derived; int /*<<< orphan*/  ctx; TYPE_1__ image; int /*<<< orphan*/  id; int /*<<< orphan*/  display; } ;
struct priv {int dummy; } ;
struct mp_image {scalar_t__ w; scalar_t__ h; int /*<<< orphan*/  imgfmt; } ;
typedef  int /*<<< orphan*/  VAStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VA_STATUS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_image_copy (struct mp_image*,struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vaPutImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  va_image_map (int /*<<< orphan*/ ,TYPE_1__*,struct mp_image*) ; 
 int /*<<< orphan*/  va_image_unmap (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ va_surface_alloc_imgfmt (struct priv*,struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_surface_image_destroy (struct va_surface*) ; 
 struct va_surface* va_surface_in_mp_image (struct mp_image*) ; 

__attribute__((used)) static int va_surface_upload(struct priv *priv, struct mp_image *va_dst,
                             struct mp_image *sw_src)
{
    struct va_surface *p = va_surface_in_mp_image(va_dst);
    if (!p)
        return -1;

    if (va_surface_alloc_imgfmt(priv, va_dst, sw_src->imgfmt) < 0)
        return -1;

    struct mp_image img;
    if (!va_image_map(p->ctx, &p->image, &img))
        return -1;
    assert(sw_src->w <= img.w && sw_src->h <= img.h);
    mp_image_set_size(&img, sw_src->w, sw_src->h); // copy only visible part
    mp_image_copy(&img, sw_src);
    va_image_unmap(p->ctx, &p->image);

    if (!p->is_derived) {
        VAStatus status = vaPutImage(p->display, p->id,
                                     p->image.image_id,
                                     0, 0, sw_src->w, sw_src->h,
                                     0, 0, sw_src->w, sw_src->h);
        if (!CHECK_VA_STATUS(p->ctx, "vaPutImage()"))
            return -1;
    }

    if (p->is_derived)
        va_surface_image_destroy(p);
    return 0;
}