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
struct vo {int /*<<< orphan*/  dheight; int /*<<< orphan*/  dwidth; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  sdl; int /*<<< orphan*/  mpv; } ;
struct priv {TYPE_1__ osd_format; int /*<<< orphan*/  renderer; } ;
struct mp_image {int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo*,char*) ; 
 scalar_t__ SDL_RenderReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mp_image* mp_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

__attribute__((used)) static struct mp_image *get_window_screenshot(struct vo *vo)
{
    struct priv *vc = vo->priv;
    struct mp_image *image = mp_image_alloc(vc->osd_format.mpv, vo->dwidth,
                                                                vo->dheight);
    if (!image)
        return NULL;
    if (SDL_RenderReadPixels(vc->renderer, NULL, vc->osd_format.sdl,
                             image->planes[0], image->stride[0])) {
        MP_ERR(vo, "SDL_RenderReadPixels failed\n");
        talloc_free(image);
        return NULL;
    }
    return image;
}