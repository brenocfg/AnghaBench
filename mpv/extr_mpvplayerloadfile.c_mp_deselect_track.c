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
struct track {int /*<<< orphan*/  type; scalar_t__ selected; } ;
struct MPContext {int dummy; } ;

/* Variables and functions */
 int NUM_PTRACKS ; 
 int /*<<< orphan*/  mp_switch_track_n (struct MPContext*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mp_deselect_track(struct MPContext *mpctx, struct track *track)
{
    if (track && track->selected) {
        for (int t = 0; t < NUM_PTRACKS; t++)
            mp_switch_track_n(mpctx, t, track->type, NULL, 0);
    }
}