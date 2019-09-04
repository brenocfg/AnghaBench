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
struct vo {struct priv* priv; } ;
struct mp_image_params {int /*<<< orphan*/  imgfmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct priv {struct mp_image_params image_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFMT_VAAPI ; 
 int /*<<< orphan*/  alloc_swdec_surfaces (struct priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_video_specific (struct priv*) ; 
 int /*<<< orphan*/  resize (struct priv*) ; 
 int /*<<< orphan*/  vo_x11_config_vo_window (struct vo*) ; 

__attribute__((used)) static int reconfig(struct vo *vo, struct mp_image_params *params)
{
    struct priv *p = vo->priv;

    free_video_specific(p);

    vo_x11_config_vo_window(vo);

    if (params->imgfmt != IMGFMT_VAAPI) {
        if (!alloc_swdec_surfaces(p, params->w, params->h, params->imgfmt))
            return -1;
    }

    p->image_params = *params;
    resize(p);
    return 0;
}