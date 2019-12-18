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
struct mp_cmd_ctx {int /*<<< orphan*/  on_osd; struct MPContext* mpctx; } ;
struct MPContext {TYPE_1__* opts; int /*<<< orphan*/  demuxer; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ab_loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PROPERTY_SET ; 
 double demux_probe_cache_dump_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_property_do (char*,int /*<<< orphan*/ ,double*,struct MPContext*) ; 
 int /*<<< orphan*/  show_property_osd (struct MPContext*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmd_align_cache_ab(void *p)
{
    struct mp_cmd_ctx *cmd = p;
    struct MPContext *mpctx = cmd->mpctx;

    if (!mpctx->demuxer)
        return;

    double a = demux_probe_cache_dump_target(mpctx->demuxer,
                                             mpctx->opts->ab_loop[0], false);
    double b = demux_probe_cache_dump_target(mpctx->demuxer,
                                             mpctx->opts->ab_loop[1], true);

    mp_property_do("ab-loop-a", M_PROPERTY_SET, &a, mpctx);
    mp_property_do("ab-loop-b", M_PROPERTY_SET, &b, mpctx);

    // Happens to cover both properties.
    show_property_osd(mpctx, "ab-loop-b", cmd->on_osd);
}