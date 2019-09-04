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
struct demux_ctrl_stream_ctrl {int member_0; void* member_1; int res; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEMUXER_CTRL_STREAM_CTRL ; 
 int /*<<< orphan*/  STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  demux_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct demux_ctrl_stream_ctrl*) ; 

int demux_stream_control(demuxer_t *demuxer, int ctrl, void *arg)
{
    struct demux_ctrl_stream_ctrl c = {ctrl, arg, STREAM_UNSUPPORTED};
    demux_control(demuxer, DEMUXER_CTRL_STREAM_CTRL, &c);
    return c.res;
}