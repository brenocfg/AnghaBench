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
struct MPContext {int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 scalar_t__ osd_get_render_subs_in_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_subtitles (struct MPContext*,double) ; 

__attribute__((used)) static void filter_update_subtitles(void *ctx, double pts)
{
    struct MPContext *mpctx = ctx;

    if (osd_get_render_subs_in_filter(mpctx->osd))
        update_subtitles(mpctx, pts);
}