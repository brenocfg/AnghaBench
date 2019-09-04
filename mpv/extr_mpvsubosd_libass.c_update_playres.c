#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_osd_res {double w; double display_par; int /*<<< orphan*/  h; } ;
struct ass_state {int res_y; double res_x; int /*<<< orphan*/  render; TYPE_1__* track; } ;
struct TYPE_2__ {int PlayResX; int PlayResY; } ;
typedef  TYPE_1__ ASS_Track ;

/* Variables and functions */
 double MPMAX (int /*<<< orphan*/ ,int) ; 
 int MP_ASS_FONT_PLAYRESY ; 
 int /*<<< orphan*/  ass_set_frame_size (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void update_playres(struct ass_state *ass, struct mp_osd_res *vo_res)
{
    ASS_Track *track = ass->track;
    int old_res_x = track->PlayResX;
    int old_res_y = track->PlayResY;

    double aspect = 1.0 * vo_res->w / MPMAX(vo_res->h, 1);
    if (vo_res->display_par > 0)
        aspect = aspect / vo_res->display_par;

    track->PlayResY = ass->res_y ? ass->res_y : MP_ASS_FONT_PLAYRESY;
    track->PlayResX = ass->res_x ? ass->res_x : track->PlayResY * aspect;

    // Force libass to clear its internal cache - it doesn't check for
    // PlayRes changes itself.
    if (old_res_x != track->PlayResX || old_res_y != track->PlayResY)
        ass_set_frame_size(ass->render, 1, 1);
}