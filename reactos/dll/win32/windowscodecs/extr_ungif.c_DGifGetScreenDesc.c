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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int SortFlag; int ColorCount; TYPE_1__* Colors; } ;
struct TYPE_9__ {int SColorResolution; int SBackGroundColor; int SAspectRatio; TYPE_4__* SColorMap; int /*<<< orphan*/  SHeight; int /*<<< orphan*/  SWidth; } ;
struct TYPE_8__ {int Red; int Green; int Blue; } ;
typedef  TYPE_2__ GifFileType ;
typedef  int GifByteType ;

/* Variables and functions */
 scalar_t__ DGifGetWord (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeMapObject (TYPE_4__*) ; 
 scalar_t__ GIF_ERROR ; 
 int GIF_OK ; 
 TYPE_4__* MakeMapObject (int,int /*<<< orphan*/ *) ; 
 int READ (TYPE_2__*,int*,int) ; 

__attribute__((used)) static int
DGifGetScreenDesc(GifFileType * GifFile) {

    int i, BitsPerPixel, SortFlag;
    GifByteType Buf[3];

    /* Put the screen descriptor into the file: */
    if (DGifGetWord(GifFile, &GifFile->SWidth) == GIF_ERROR ||
        DGifGetWord(GifFile, &GifFile->SHeight) == GIF_ERROR)
        return GIF_ERROR;

    if (READ(GifFile, Buf, 3) != 3) {
        return GIF_ERROR;
    }
    GifFile->SColorResolution = (((Buf[0] & 0x70) + 1) >> 4) + 1;
    SortFlag = (Buf[0] & 0x08) != 0;
    BitsPerPixel = (Buf[0] & 0x07) + 1;
    GifFile->SBackGroundColor = Buf[1];
    GifFile->SAspectRatio = Buf[2];
    if (Buf[0] & 0x80) {    /* Do we have global color map? */

        GifFile->SColorMap = MakeMapObject(1 << BitsPerPixel, NULL);
        if (GifFile->SColorMap == NULL) {
            return GIF_ERROR;
        }

        /* Get the global color map: */
        GifFile->SColorMap->SortFlag = SortFlag;
        for (i = 0; i < GifFile->SColorMap->ColorCount; i++) {
            if (READ(GifFile, Buf, 3) != 3) {
                FreeMapObject(GifFile->SColorMap);
                GifFile->SColorMap = NULL;
                return GIF_ERROR;
            }
            GifFile->SColorMap->Colors[i].Red = Buf[0];
            GifFile->SColorMap->Colors[i].Green = Buf[1];
            GifFile->SColorMap->Colors[i].Blue = Buf[2];
        }
    } else {
        GifFile->SColorMap = NULL;
    }

    return GIF_OK;
}