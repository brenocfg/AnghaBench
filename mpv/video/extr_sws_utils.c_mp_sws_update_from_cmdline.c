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
struct sws_opts {int /*<<< orphan*/  zimg; scalar_t__ bitexact; int /*<<< orphan*/  fast; int /*<<< orphan*/  scaler; int /*<<< orphan*/  chr_vshift; int /*<<< orphan*/  chr_hshift; int /*<<< orphan*/  chr_sharpen; int /*<<< orphan*/  lum_sharpen; int /*<<< orphan*/  chr_gblur; int /*<<< orphan*/  lum_gblur; } ;
struct mp_sws_context {int force_reload; int /*<<< orphan*/  allow_zimg; int /*<<< orphan*/  flags; int /*<<< orphan*/  src_filter; TYPE_1__* opts_cache; } ;
struct TYPE_2__ {struct sws_opts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWS_BITEXACT ; 
 int /*<<< orphan*/  SWS_PRINT_INFO ; 
 int /*<<< orphan*/  m_config_cache_update (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_sws_hq_flags ; 
 int /*<<< orphan*/  sws_freeFilter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_getDefaultFilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mp_sws_update_from_cmdline(struct mp_sws_context *ctx)
{
    m_config_cache_update(ctx->opts_cache);
    struct sws_opts *opts = ctx->opts_cache->opts;

    sws_freeFilter(ctx->src_filter);
    ctx->src_filter = sws_getDefaultFilter(opts->lum_gblur, opts->chr_gblur,
                                           opts->lum_sharpen, opts->chr_sharpen,
                                           opts->chr_hshift, opts->chr_vshift, 0);
    ctx->force_reload = true;

    ctx->flags = SWS_PRINT_INFO;
    ctx->flags |= opts->scaler;
    if (!opts->fast)
        ctx->flags |= mp_sws_hq_flags;
    if (opts->bitexact)
        ctx->flags |= SWS_BITEXACT;

    ctx->allow_zimg = opts->zimg;
}