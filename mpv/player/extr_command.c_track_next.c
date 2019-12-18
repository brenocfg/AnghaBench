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
struct track {int type; int /*<<< orphan*/  selected; } ;
struct MPContext {int num_tracks; struct track** tracks; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static struct track* track_next(struct MPContext *mpctx, enum stream_type type,
                                int direction, struct track *track)
{
    assert(direction == -1 || direction == +1);
    struct track *prev = NULL, *next = NULL;
    bool seen = track == NULL;
    for (int n = 0; n < mpctx->num_tracks; n++) {
        struct track *cur = mpctx->tracks[n];
        if (cur->type == type) {
            if (cur == track) {
                seen = true;
            } else if (!cur->selected) {
                if (seen && !next) {
                    next = cur;
                }
                if (!seen || !track) {
                    prev = cur;
                }
            }
        }
    }
    return direction > 0 ? next : prev;
}