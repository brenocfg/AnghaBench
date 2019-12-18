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
struct track {scalar_t__ d_sub; } ;
struct MPContext {int /*<<< orphan*/  play_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  sub_reset (scalar_t__) ; 
 int /*<<< orphan*/  sub_set_play_dir (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_osd_set_subs (struct MPContext*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_subtitles(struct MPContext *mpctx, struct track *track)
{
    if (track->d_sub) {
        sub_reset(track->d_sub);
        sub_set_play_dir(track->d_sub, mpctx->play_dir);
    }
    term_osd_set_subs(mpctx, NULL);
}