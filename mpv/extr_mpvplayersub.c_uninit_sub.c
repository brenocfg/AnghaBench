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
struct track {int /*<<< orphan*/ * d_sub; } ;
struct MPContext {int /*<<< orphan*/  osd; } ;

/* Variables and functions */
 int get_order (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  osd_set_sub (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_subtitles (struct MPContext*,struct track*) ; 
 int /*<<< orphan*/  sub_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sub_select (int /*<<< orphan*/ *,int) ; 

void uninit_sub(struct MPContext *mpctx, struct track *track)
{
    if (track && track->d_sub) {
        reset_subtitles(mpctx, track);
        sub_select(track->d_sub, false);
        int order = get_order(mpctx, track);
        osd_set_sub(mpctx->osd, order, NULL);
        sub_destroy(track->d_sub);
        track->d_sub = NULL;
    }
}