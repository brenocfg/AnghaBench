#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {scalar_t__* streams; int /*<<< orphan*/  slave; int /*<<< orphan*/  num_streams; } ;
struct TYPE_3__ {struct priv* priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int MPMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int demux_get_num_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_get_stream (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  demux_stream_is_selected (scalar_t__) ; 
 int /*<<< orphan*/  demuxer_select_track (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reselect_streams(demuxer_t *demuxer)
{
    struct priv *p = demuxer->priv;
    int num_slave = demux_get_num_stream(p->slave);
    for (int n = 0; n < MPMIN(num_slave, p->num_streams); n++) {
        if (p->streams[n]) {
            demuxer_select_track(p->slave, demux_get_stream(p->slave, n),
                MP_NOPTS_VALUE, demux_stream_is_selected(p->streams[n]));
        }
    }
}