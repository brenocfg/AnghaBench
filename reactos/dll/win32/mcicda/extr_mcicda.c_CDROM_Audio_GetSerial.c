#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_6__ {int FirstTrack; int LastTrack; TYPE_1__* TrackData; } ;
struct TYPE_5__ {int* Address; } ;
typedef  int DWORD ;
typedef  TYPE_2__ CDROM_TOC ;

/* Variables and functions */
 int FRAME_OF_TOC (TYPE_2__,int) ; 

__attribute__((used)) static DWORD CDROM_Audio_GetSerial(CDROM_TOC* toc)
{
    DWORD serial = 0;
    int i;
    WORD wMagic;
    DWORD dwStart, dwEnd;

    /*
     * wMagic collects the wFrames from track 1
     * dwStart, dwEnd collect the beginning and end of the disc respectively, in
     * frames.
     * There it is collected for correcting the serial when there are less than
     * 3 tracks.
     */
    wMagic = toc->TrackData[0].Address[3];
    dwStart = FRAME_OF_TOC(*toc, toc->FirstTrack);

    for (i = 0; i <= toc->LastTrack - toc->FirstTrack; i++) {
        serial += (toc->TrackData[i].Address[1] << 16) |
            (toc->TrackData[i].Address[2] << 8) | toc->TrackData[i].Address[3];
    }
    dwEnd = FRAME_OF_TOC(*toc, toc->LastTrack + 1);

    if (toc->LastTrack - toc->FirstTrack + 1 < 3)
        serial += wMagic + (dwEnd - dwStart);

    return serial;
}