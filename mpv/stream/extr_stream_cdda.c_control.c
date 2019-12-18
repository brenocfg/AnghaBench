#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* priv; } ;
typedef  TYPE_3__ stream_t ;
typedef  double int64_t ;
struct TYPE_10__ {TYPE_2__* cd; int /*<<< orphan*/  end_sector; int /*<<< orphan*/  start_sector; } ;
typedef  TYPE_4__ cdda_priv ;
struct TYPE_8__ {TYPE_1__* disc_toc; } ;
struct TYPE_7__ {double dwStartSector; } ;

/* Variables and functions */
 double CDIO_CD_FRAMESIZE_RAW ; 
#define  STREAM_CTRL_GET_CHAPTER_TIME 129 
#define  STREAM_CTRL_GET_NUM_CHAPTERS 128 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 int get_track_by_sector (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int control(stream_t *stream, int cmd, void *arg)
{
    cdda_priv *p = stream->priv;
    switch (cmd) {
    case STREAM_CTRL_GET_NUM_CHAPTERS:
    {
        int start_track = get_track_by_sector(p, p->start_sector);
        int end_track = get_track_by_sector(p, p->end_sector);
        if (start_track == -1 || end_track == -1)
            return STREAM_ERROR;
        *(unsigned int *)arg = end_track + 1 - start_track;
        return STREAM_OK;
    }
    case STREAM_CTRL_GET_CHAPTER_TIME:
    {
        int track = *(double *)arg;
        int start_track = get_track_by_sector(p, p->start_sector);
        int end_track = get_track_by_sector(p, p->end_sector);
        track += start_track;
        if (track > end_track)
            return STREAM_ERROR;
        int64_t sector = p->cd->disc_toc[track].dwStartSector;
        int64_t pos = sector * CDIO_CD_FRAMESIZE_RAW;
        // Assume standard audio CD: 44.1khz, 2 channels, s16 samples
        *(double *)arg = pos / (44100.0 * 2 * 2);
        return STREAM_OK;
    }
    }
    return STREAM_UNSUPPORTED;
}