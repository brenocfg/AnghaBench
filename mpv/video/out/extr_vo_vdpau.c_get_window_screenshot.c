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
struct vo {scalar_t__ dwidth; scalar_t__ dheight; struct vdpctx* priv; } ;
struct vdpctx {int /*<<< orphan*/ * output_surfaces; int /*<<< orphan*/  num_output_surfaces; int /*<<< orphan*/  surface_num; } ;
struct mp_image {scalar_t__ w; scalar_t__ h; } ;
typedef  int /*<<< orphan*/  VdpOutputSurface ;

/* Variables and functions */
 int WRAP_ADD (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,scalar_t__,scalar_t__) ; 
 struct mp_image* read_output_surface (struct vo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mp_image *get_window_screenshot(struct vo *vo)
{
    struct vdpctx *vc = vo->priv;
    int last_surface = WRAP_ADD(vc->surface_num, -1, vc->num_output_surfaces);
    VdpOutputSurface screen = vc->output_surfaces[last_surface];
    struct mp_image *image = read_output_surface(vo, screen);
    if (image && image->w >= vo->dwidth && image->h >= vo->dheight)
        mp_image_set_size(image, vo->dwidth, vo->dheight);
    return image;
}