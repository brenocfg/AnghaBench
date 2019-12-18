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
struct TYPE_9__ {scalar_t__ priv; } ;
typedef  TYPE_3__ stream_t ;
typedef  int int64_t ;
struct TYPE_10__ {int start_sector; int end_sector; int sector; int /*<<< orphan*/  cdp; TYPE_2__* cd; } ;
typedef  TYPE_4__ cdda_priv ;
struct TYPE_8__ {int tracks; TYPE_1__* disc_toc; } ;
struct TYPE_7__ {int dwStartSector; } ;

/* Variables and functions */
 int CDIO_CD_FRAMESIZE_RAW ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  paranoia_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_track_info (TYPE_3__*,int) ; 

__attribute__((used)) static int seek(stream_t *s, int64_t newpos)
{
    cdda_priv *p = (cdda_priv *)s->priv;
    int sec;
    int current_track = 0, seeked_track = 0;
    int seek_to_track = 0;
    int i;

    newpos += p->start_sector * CDIO_CD_FRAMESIZE_RAW;

    sec = newpos / CDIO_CD_FRAMESIZE_RAW;
    if (newpos < 0 || sec > p->end_sector) {
        p->sector = p->end_sector + 1;
        return 0;
    }

    for (i = 0; i < p->cd->tracks; i++) {
        if (p->sector >= p->cd->disc_toc[i].dwStartSector
            && p->sector < p->cd->disc_toc[i + 1].dwStartSector)
            current_track = i;
        if (sec >= p->cd->disc_toc[i].dwStartSector
            && sec < p->cd->disc_toc[i + 1].dwStartSector)
        {
            seeked_track = i;
            seek_to_track = sec == p->cd->disc_toc[i].dwStartSector;
        }
    }
    if (current_track != seeked_track && !seek_to_track)
        print_track_info(s, seeked_track + 1);

    p->sector = sec;

    paranoia_seek(p->cdp, sec, SEEK_SET);
    return 1;
}