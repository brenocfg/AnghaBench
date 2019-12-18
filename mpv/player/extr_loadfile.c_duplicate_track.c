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
struct track {int dummy; } ;
struct MPContext {struct track*** current_track; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;

/* Variables and functions */

__attribute__((used)) static bool duplicate_track(struct MPContext *mpctx, int order,
                            enum stream_type type, struct track *track)
{
    for (int i = 0; i < order; i++) {
        if (mpctx->current_track[i][type] == track)
            return true;
    }
    return false;
}