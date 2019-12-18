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
struct sub {double pts; double endpts; int /*<<< orphan*/  valid; } ;
struct sd_lavc_priv {double current_pts; struct sub* subs; } ;
struct sd {struct sd_lavc_priv* priv; } ;

/* Variables and functions */
 int MAX_QUEUE ; 
 double MP_NOPTS_VALUE ; 

__attribute__((used)) static bool accepts_packet(struct sd *sd, double min_pts)
{
    struct sd_lavc_priv *priv = sd->priv;

    double pts = priv->current_pts;
    if (min_pts != MP_NOPTS_VALUE) {
        // guard against bogus rendering PTS in the future.
        if (pts == MP_NOPTS_VALUE || min_pts < pts)
            pts = min_pts;
        // Heuristic: we assume rendering cannot lag behind more than 1 second
        // behind decoding.
        if (pts + 1 < min_pts)
            pts = min_pts;
    }

    int last_needed = -1;
    for (int n = 0; n < MAX_QUEUE; n++) {
        struct sub *sub = &priv->subs[n];
        if (!sub->valid)
            continue;
        if (pts == MP_NOPTS_VALUE ||
            ((sub->pts == MP_NOPTS_VALUE || sub->pts >= pts) ||
             (sub->endpts == MP_NOPTS_VALUE || pts < sub->endpts)))
        {
            last_needed = n;
        }
    }
    // We can accept a packet if it wouldn't overflow the fixed subtitle queue.
    // We assume that get_bitmaps() never decreases the PTS.
    return last_needed + 1 < MAX_QUEUE;
}