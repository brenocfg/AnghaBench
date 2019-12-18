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
struct mp_zimg_context {scalar_t__ opts_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_zimg (struct mp_zimg_context*) ; 
 scalar_t__ m_config_cache_alloc (struct mp_zimg_context*,struct mpv_global*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_zimg_update_from_cmdline (struct mp_zimg_context*) ; 
 int /*<<< orphan*/  zimg_conf ; 

void mp_zimg_enable_cmdline_opts(struct mp_zimg_context *ctx,
                                 struct mpv_global *g)
{
    if (ctx->opts_cache)
        return;

    ctx->opts_cache = m_config_cache_alloc(ctx, g, &zimg_conf);
    destroy_zimg(ctx); // force update
    mp_zimg_update_from_cmdline(ctx); // first update
}