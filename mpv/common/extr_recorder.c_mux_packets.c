#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_recorder_sink {int num_packets; TYPE_1__** packets; struct mp_recorder* owner; } ;
struct mp_recorder {int /*<<< orphan*/  muxing; } ;
struct TYPE_5__ {scalar_t__ keyframe; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  mux_packet (struct mp_recorder_sink*,TYPE_1__*) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

__attribute__((used)) static void mux_packets(struct mp_recorder_sink *rst, bool force)
{
    struct mp_recorder *priv = rst->owner;
    if (!priv->muxing || !rst->num_packets)
        return;

    int safe_count = 0;
    for (int n = 0; n < rst->num_packets; n++) {
        if (rst->packets[n]->keyframe)
            safe_count = n;
    }
    if (force)
        safe_count = rst->num_packets;

    for (int n = 0; n < safe_count; n++) {
        mux_packet(rst, rst->packets[n]);
        talloc_free(rst->packets[n]);
    }

    // Remove packets[0..safe_count]
    memmove(&rst->packets[0], &rst->packets[safe_count],
            (rst->num_packets - safe_count) * sizeof(rst->packets[0]));
    rst->num_packets -= safe_count;
}