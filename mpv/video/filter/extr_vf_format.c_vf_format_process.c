#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct priv {TYPE_3__* opts; TYPE_4__* conv; } ;
struct TYPE_5__ {int /*<<< orphan*/  levels; } ;
struct mp_image_params {int imgfmt; scalar_t__ hw_subfmt; TYPE_1__ color; } ;
struct mp_image {int imgfmt; struct mp_image_params params; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct priv* priv; } ;
struct TYPE_8__ {TYPE_2__* f; } ;
struct TYPE_7__ {int fmt; scalar_t__ convert; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 scalar_t__ MP_CSP_AUTO ; 
 int /*<<< orphan*/  MP_CSP_LEVELS_TV ; 
 scalar_t__ MP_CSP_RGB ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  mp_autoconvert_set_target_image_params (TYPE_4__*,struct mp_image_params*) ; 
 int /*<<< orphan*/  mp_image_params_guess_csp (struct mp_image_params*) ; 
 scalar_t__ mp_imgfmt_get_forced_csp (int) ; 
 scalar_t__ mp_pin_can_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_params (TYPE_3__*,struct mp_image_params*) ; 

__attribute__((used)) static void vf_format_process(struct mp_filter *f)
{
    struct priv *priv = f->priv;

    if (mp_pin_can_transfer_data(priv->conv->f->pins[0], f->ppins[0])) {
        struct mp_frame frame = mp_pin_out_read(f->ppins[0]);

        if (priv->opts->convert && frame.type == MP_FRAME_VIDEO) {
            struct mp_image *img = frame.data;
            struct mp_image_params par = img->params;
            int outfmt = priv->opts->fmt;

            // If we convert from RGB to YUV, default to limited range.
            if (mp_imgfmt_get_forced_csp(img->imgfmt) == MP_CSP_RGB &&
                outfmt && mp_imgfmt_get_forced_csp(outfmt) == MP_CSP_AUTO)
            {
                par.color.levels = MP_CSP_LEVELS_TV;
            }

            set_params(priv->opts, &par);

            if (par.imgfmt != outfmt) {
                par.imgfmt = outfmt;
                par.hw_subfmt = 0;
            }
            mp_image_params_guess_csp(&par);

            mp_autoconvert_set_target_image_params(priv->conv, &par);
        }

        mp_pin_in_write(priv->conv->f->pins[0], frame);
    }

    if (mp_pin_can_transfer_data(f->ppins[1], priv->conv->f->pins[1])) {
        struct mp_frame frame = mp_pin_out_read(priv->conv->f->pins[1]);

        if (!priv->opts->convert && frame.type == MP_FRAME_VIDEO) {
            struct mp_image *img = frame.data;

            set_params(priv->opts, &img->params);
            mp_image_params_guess_csp(&img->params);
        }

        mp_pin_in_write(f->ppins[1], frame);
    }
}