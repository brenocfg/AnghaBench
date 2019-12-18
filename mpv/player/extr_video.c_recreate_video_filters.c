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
struct vo_chain {int /*<<< orphan*/  filter; } ;
struct MPOpts {int /*<<< orphan*/  vf_settings; } ;
struct MPContext {struct vo_chain* vo_chain; struct MPOpts* opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct vo_chain*) ; 
 int mp_output_chain_update_filters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool recreate_video_filters(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    struct vo_chain *vo_c = mpctx->vo_chain;
    assert(vo_c);

    return mp_output_chain_update_filters(vo_c->filter, opts->vf_settings);
}