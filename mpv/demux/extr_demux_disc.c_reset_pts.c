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
struct priv {double base_time; int seek_reinit; int /*<<< orphan*/  last_dts; int /*<<< orphan*/  base_dts; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream; struct priv* priv; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*,double) ; 
 int /*<<< orphan*/  STREAM_CTRL_GET_CURRENT_TIME ; 
 int stream_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static void reset_pts(demuxer_t *demuxer)
{
    struct priv *p = demuxer->priv;

    double base;
    if (stream_control(demuxer->stream, STREAM_CTRL_GET_CURRENT_TIME, &base) < 1)
        base = 0;

    MP_VERBOSE(demuxer, "reset to time: %f\n", base);

    p->base_dts = p->last_dts = MP_NOPTS_VALUE;
    p->base_time = base;
    p->seek_reinit = false;
}