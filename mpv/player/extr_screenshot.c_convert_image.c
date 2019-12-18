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
struct mpv_global {int dummy; } ;
struct mp_image_params {int imgfmt; int w; int h; int p_w; int p_h; } ;
struct mp_sws_context {struct mp_log* log; struct mp_image_params params; } ;
struct mp_log {int dummy; } ;
struct mp_image {struct mp_log* log; struct mp_image_params params; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_err (struct mp_log*,char*) ; 
 struct mp_sws_context* mp_image_alloc (int,int,int) ; 
 int /*<<< orphan*/  mp_image_copy_attributes (struct mp_sws_context*,struct mp_sws_context*) ; 
 struct mp_sws_context* mp_image_new_ref (struct mp_sws_context*) ; 
 scalar_t__ mp_image_params_equal (struct mp_image_params*,struct mp_image_params*) ; 
 int /*<<< orphan*/  mp_image_params_get_dsize (struct mp_image_params*,int*,int*) ; 
 int /*<<< orphan*/  mp_image_params_guess_csp (struct mp_image_params*) ; 
 struct mp_sws_context* mp_sws_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sws_enable_cmdline_opts (struct mp_sws_context*,struct mpv_global*) ; 
 scalar_t__ mp_sws_scale (struct mp_sws_context*,struct mp_sws_context*,struct mp_sws_context*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_sws_context*) ; 

struct mp_image *convert_image(struct mp_image *image, int destfmt,
                               struct mpv_global *global, struct mp_log *log)
{
    int d_w, d_h;
    mp_image_params_get_dsize(&image->params, &d_w, &d_h);

    struct mp_image_params p = {
        .imgfmt = destfmt,
        .w = d_w,
        .h = d_h,
        .p_w = 1,
        .p_h = 1,
    };
    mp_image_params_guess_csp(&p);

    if (mp_image_params_equal(&p, &image->params))
        return mp_image_new_ref(image);

    struct mp_image *dst = mp_image_alloc(p.imgfmt, p.w, p.h);
    if (!dst) {
        mp_err(log, "Out of memory.\n");
        return NULL;
    }
    mp_image_copy_attributes(dst, image);

    dst->params = p;

    struct mp_sws_context *sws = mp_sws_alloc(NULL);
    sws->log = log;
    if (global)
        mp_sws_enable_cmdline_opts(sws, global);
    bool ok = mp_sws_scale(sws, dst, image) >= 0;
    talloc_free(sws);

    if (!ok) {
        mp_err(log, "Error when converting image.\n");
        talloc_free(dst);
        return NULL;
    }

    return dst;
}