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
struct MPContext {int num_tracks; int /*<<< orphan*/ * recorder; int /*<<< orphan*/ * tracks; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_recorder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_track_recorder_sink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void close_recorder(struct MPContext *mpctx)
{
    if (!mpctx->recorder)
        return;

    for (int n = 0; n < mpctx->num_tracks; n++)
        set_track_recorder_sink(mpctx->tracks[n], NULL);

    mp_recorder_destroy(mpctx->recorder);
    mpctx->recorder = NULL;
}