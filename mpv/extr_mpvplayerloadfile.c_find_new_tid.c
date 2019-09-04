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
struct track {int type; int /*<<< orphan*/  user_tid; } ;
struct MPContext {int num_tracks; struct track** tracks; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;

/* Variables and functions */
 int MPMAX (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_new_tid(struct MPContext *mpctx, enum stream_type t)
{
    int new_id = 0;
    for (int i = 0; i < mpctx->num_tracks; i++) {
        struct track *track = mpctx->tracks[i];
        if (track->type == t)
            new_id = MPMAX(new_id, track->user_tid);
    }
    return new_id + 1;
}