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
struct sd {scalar_t__ start; TYPE_1__* driver; int /*<<< orphan*/  end; int /*<<< orphan*/  codec; } ;
struct dec_sub {scalar_t__ last_vo_pts; scalar_t__ start; struct sd* new_segment; struct sd* sd; int /*<<< orphan*/  end; int /*<<< orphan*/  codec; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* decode ) (struct sd*,struct sd*) ;int /*<<< orphan*/  (* uninit ) (struct sd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct dec_sub*,char*) ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct dec_sub*,char*,scalar_t__,scalar_t__) ; 
 struct sd* init_decoder (struct dec_sub*) ; 
 int /*<<< orphan*/  stub1 (struct sd*) ; 
 int /*<<< orphan*/  stub2 (struct sd*,struct sd*) ; 
 int /*<<< orphan*/  talloc_free (struct sd*) ; 
 int /*<<< orphan*/  update_subtitle_speed (struct dec_sub*) ; 

__attribute__((used)) static void update_segment(struct dec_sub *sub)
{
    if (sub->new_segment && sub->last_vo_pts != MP_NOPTS_VALUE &&
        sub->last_vo_pts >= sub->new_segment->start)
    {
        MP_VERBOSE(sub, "Switch segment: %f at %f\n", sub->new_segment->start,
                   sub->last_vo_pts);

        sub->codec = sub->new_segment->codec;
        sub->start = sub->new_segment->start;
        sub->end = sub->new_segment->end;
        struct sd *new = init_decoder(sub);
        if (new) {
            sub->sd->driver->uninit(sub->sd);
            talloc_free(sub->sd);
            sub->sd = new;
            update_subtitle_speed(sub);
        } else {
            // We'll just keep the current decoder, and feed it possibly
            // invalid data (not our fault if it crashes or something).
            MP_ERR(sub, "Can't change to new codec.\n");
        }
        sub->sd->driver->decode(sub->sd, sub->new_segment);
        talloc_free(sub->new_segment);
        sub->new_segment = NULL;
    }
}