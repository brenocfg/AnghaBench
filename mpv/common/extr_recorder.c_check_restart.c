#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_recorder_sink {double max_out_pts; int num_packets; TYPE_2__** packets; TYPE_1__* sh; int /*<<< orphan*/  proper_eof; } ;
struct mp_recorder {int muxing; int num_streams; double rebase_ts; double base_ts; int /*<<< orphan*/  muxing_from_start; struct mp_recorder_sink** streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  pts; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double MP_PTS_MAX (double,double) ; 
 double MP_PTS_MIN (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_WARN (struct mp_recorder*,char*,double) ; 
 int QUEUE_MIN_PACKETS ; 
 scalar_t__ STREAM_SUB ; 
 scalar_t__ STREAM_VIDEO ; 

__attribute__((used)) static void check_restart(struct mp_recorder *priv)
{
    if (priv->muxing)
        return;

    double min_ts = MP_NOPTS_VALUE;
    double rebase_ts = 0;
    for (int n = 0; n < priv->num_streams; n++) {
        struct mp_recorder_sink *rst = priv->streams[n];
        int min_packets = rst->sh->type == STREAM_VIDEO ? QUEUE_MIN_PACKETS : 1;

        rebase_ts = MP_PTS_MAX(rebase_ts, rst->max_out_pts);

        if (rst->num_packets < min_packets) {
            if (!rst->proper_eof && rst->sh->type != STREAM_SUB)
                return;
            continue;
        }

        for (int i = 0; i < min_packets; i++)
            min_ts = MP_PTS_MIN(min_ts, rst->packets[i]->pts);
    }

    // Subtitle only stream (wait longer) or stream without any PTS (fuck it).
    if (min_ts == MP_NOPTS_VALUE)
        return;

    priv->rebase_ts = rebase_ts;
    priv->base_ts = min_ts;

    for (int n = 0; n < priv->num_streams; n++) {
        struct mp_recorder_sink *rst = priv->streams[n];
        rst->max_out_pts = min_ts;
    }

    priv->muxing = true;

    if (!priv->muxing_from_start)
        MP_WARN(priv, "Discontinuity at timestamp %f.\n", priv->rebase_ts);
}