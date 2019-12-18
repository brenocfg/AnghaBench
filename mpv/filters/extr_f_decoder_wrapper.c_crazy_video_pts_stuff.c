#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fps; } ;
struct priv {scalar_t__ codec_pts; scalar_t__ num_codec_pts_problems; scalar_t__ codec_dts; scalar_t__ num_codec_dts_problems; int has_broken_packet_pts; TYPE_3__ public; TYPE_2__* decoder; TYPE_1__* codec; } ;
struct mp_image {scalar_t__ pts; scalar_t__ dts; } ;
struct TYPE_5__ {int /*<<< orphan*/  f; int /*<<< orphan*/  (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_4__ {scalar_t__ avi_dts; } ;

/* Variables and functions */
 int MPMAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  VDCTRL_GET_BFRAMES ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void crazy_video_pts_stuff(struct priv *p, struct mp_image *mpi)
{
    // Note: the PTS is reordered, but the DTS is not. Both must be monotonic.

    if (mpi->pts != MP_NOPTS_VALUE) {
        if (mpi->pts < p->codec_pts)
            p->num_codec_pts_problems++;
        p->codec_pts = mpi->pts;
    }

    if (mpi->dts != MP_NOPTS_VALUE) {
        if (mpi->dts <= p->codec_dts)
            p->num_codec_dts_problems++;
        p->codec_dts = mpi->dts;
    }

    if (p->has_broken_packet_pts < 0)
        p->has_broken_packet_pts++;
    if (p->num_codec_pts_problems)
        p->has_broken_packet_pts = 1;

    // If PTS is unset, or non-monotonic, fall back to DTS.
    if ((p->num_codec_pts_problems > p->num_codec_dts_problems ||
        mpi->pts == MP_NOPTS_VALUE) && mpi->dts != MP_NOPTS_VALUE)
        mpi->pts = mpi->dts;

    // Compensate for incorrectly using mpeg-style DTS for avi timestamps.
    if (p->decoder && p->decoder->control && p->codec->avi_dts &&
        mpi->pts != MP_NOPTS_VALUE && p->public.fps > 0)
    {
        int delay = -1;
        p->decoder->control(p->decoder->f, VDCTRL_GET_BFRAMES, &delay);
        mpi->pts -= MPMAX(delay, 0) / p->public.fps;
    }
}