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
struct zimg_opts {int dummy; } ;
struct mp_zimg_context {struct zimg_opts opts; TYPE_1__* opts_cache; } ;
struct TYPE_2__ {struct zimg_opts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_config_cache_update (TYPE_1__*) ; 

__attribute__((used)) static void mp_zimg_update_from_cmdline(struct mp_zimg_context *ctx)
{
    m_config_cache_update(ctx->opts_cache);

    struct zimg_opts *opts = ctx->opts_cache->opts;
    ctx->opts = *opts;
}