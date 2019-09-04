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
struct demuxer {int dummy; } ;
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_stream_track (struct MPContext*,struct demuxer*,int /*<<< orphan*/ ) ; 
 int demux_get_num_stream (struct demuxer*) ; 
 int /*<<< orphan*/  demux_get_stream (struct demuxer*,int) ; 

void add_demuxer_tracks(struct MPContext *mpctx, struct demuxer *demuxer)
{
    for (int n = 0; n < demux_get_num_stream(demuxer); n++)
        add_stream_track(mpctx, demuxer, demux_get_stream(demuxer, n));
}