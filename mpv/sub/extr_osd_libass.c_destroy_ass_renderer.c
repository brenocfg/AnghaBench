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
struct ass_state {int /*<<< orphan*/ * log; int /*<<< orphan*/ * library; int /*<<< orphan*/ * render; int /*<<< orphan*/ * track; } ;

/* Variables and functions */
 int /*<<< orphan*/  ass_free_track (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_library_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_renderer_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_ass_renderer(struct ass_state *ass)
{
    if (ass->track)
        ass_free_track(ass->track);
    ass->track = NULL;
    if (ass->render)
        ass_renderer_done(ass->render);
    ass->render = NULL;
    if (ass->library)
        ass_library_done(ass->library);
    ass->library = NULL;
    talloc_free(ass->log);
    ass->log = NULL;
}