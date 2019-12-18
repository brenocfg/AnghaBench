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
struct mp_recorder_sink {int discont; int proper_eof; } ;
struct mp_recorder {int num_streams; int muxing; int muxing_from_start; struct mp_recorder_sink** streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_packets (struct mp_recorder*) ; 
 int /*<<< orphan*/  mux_packets (struct mp_recorder_sink*,int) ; 

void mp_recorder_mark_discontinuity(struct mp_recorder *priv)
{
    flush_packets(priv);

    for (int n = 0; n < priv->num_streams; n++) {
        struct mp_recorder_sink *rst = priv->streams[n];
        mux_packets(rst, true);
        rst->discont = true;
        rst->proper_eof = false;
    }

    priv->muxing = false;
    priv->muxing_from_start = false;
}