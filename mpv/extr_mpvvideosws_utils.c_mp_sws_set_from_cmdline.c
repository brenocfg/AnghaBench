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
struct sws_opts {int /*<<< orphan*/  scaler; int /*<<< orphan*/  chr_vshift; int /*<<< orphan*/  chr_hshift; int /*<<< orphan*/  chr_sharpen; int /*<<< orphan*/  lum_sharpen; int /*<<< orphan*/  chr_gblur; int /*<<< orphan*/  lum_gblur; } ;
struct mpv_global {int dummy; } ;
struct mp_sws_context {int force_reload; int /*<<< orphan*/  flags; int /*<<< orphan*/  src_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWS_PRINT_INFO ; 
 struct sws_opts* mp_get_config_group (int /*<<< orphan*/ *,struct mpv_global*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_conf ; 
 int /*<<< orphan*/  sws_freeFilter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_getDefaultFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct sws_opts*) ; 

void mp_sws_set_from_cmdline(struct mp_sws_context *ctx, struct mpv_global *g)
{
    struct sws_opts *opts = mp_get_config_group(NULL, g, &sws_conf);

    sws_freeFilter(ctx->src_filter);
    ctx->src_filter = sws_getDefaultFilter(opts->lum_gblur, opts->chr_gblur,
                                           opts->lum_sharpen, opts->chr_sharpen,
                                           opts->chr_hshift, opts->chr_vshift, 0);
    ctx->force_reload = true;

    ctx->flags = SWS_PRINT_INFO;
    ctx->flags |= opts->scaler;

    talloc_free(opts);
}