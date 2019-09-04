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
struct track {struct mp_recorder_sink* remux_sink; TYPE_1__* dec; scalar_t__ d_sub; } ;
struct mp_recorder_sink {int dummy; } ;
struct TYPE_2__ {struct mp_recorder_sink* recorder_sink; } ;

/* Variables and functions */
 int /*<<< orphan*/  sub_set_recorder_sink (scalar_t__,struct mp_recorder_sink*) ; 

__attribute__((used)) static void set_track_recorder_sink(struct track *track,
                                    struct mp_recorder_sink *sink)
{
    if (track->d_sub)
        sub_set_recorder_sink(track->d_sub, sink);
    if (track->dec)
        track->dec->recorder_sink = sink;
    track->remux_sink = sink;
}