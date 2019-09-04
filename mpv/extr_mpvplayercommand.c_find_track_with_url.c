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
struct track {int type; int /*<<< orphan*/  external_filename; scalar_t__ is_external; } ;
struct MPContext {int num_tracks; struct track** tracks; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct track *find_track_with_url(struct MPContext *mpctx, int type,
                                         const char *url)
{
    for (int n = 0; n < mpctx->num_tracks; n++) {
        struct track *track = mpctx->tracks[n];
        if (track && track->type == type && track->is_external &&
            strcmp(track->external_filename, url) == 0)
            return track;
    }
    return NULL;
}