#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct priv {int /*<<< orphan*/  slave; } ;
struct TYPE_4__ {struct priv* priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int CONTROL_OK ; 
#define  DEMUXER_CTRL_RESYNC 129 
#define  DEMUXER_CTRL_SWITCHED_TRACKS 128 
 int demux_control (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  demux_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reselect_streams (TYPE_1__*) ; 

__attribute__((used)) static int d_control(demuxer_t *demuxer, int cmd, void *arg)
{
    struct priv *p = demuxer->priv;

    switch (cmd) {
    case DEMUXER_CTRL_RESYNC:
        demux_flush(p->slave);
        break; // relay to slave demuxer
    case DEMUXER_CTRL_SWITCHED_TRACKS:
        reselect_streams(demuxer);
        return CONTROL_OK;
    }
    return demux_control(p->slave, cmd, arg);
}