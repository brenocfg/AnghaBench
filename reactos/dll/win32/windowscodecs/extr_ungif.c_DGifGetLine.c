#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int PixelCount; } ;
struct TYPE_7__ {int Width; } ;
struct TYPE_8__ {TYPE_1__ Image; TYPE_3__* Private; } ;
typedef  int /*<<< orphan*/  GifPixelType ;
typedef  TYPE_2__ GifFileType ;
typedef  TYPE_3__ GifFilePrivateType ;
typedef  int /*<<< orphan*/  GifByteType ;

/* Variables and functions */
 scalar_t__ DGifDecompressLine (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int DGifGetCodeNext (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int GIF_ERROR ; 
 scalar_t__ GIF_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static int
DGifGetLine(GifFileType * GifFile,
            GifPixelType * Line,
            int LineLen) {

    GifByteType *Dummy;
    GifFilePrivateType *Private = GifFile->Private;

    if (!LineLen)
        LineLen = GifFile->Image.Width;

    if ((Private->PixelCount -= LineLen) > 0xffff0000UL) {
        return GIF_ERROR;
    }

    if (DGifDecompressLine(GifFile, Line, LineLen) == GIF_OK) {
        if (Private->PixelCount == 0) {
            /* We probably would not be called any more, so lets clean
             * everything before we return: need to flush out all rest of
             * image until empty block (size 0) detected. We use GetCodeNext. */
            do
                if (DGifGetCodeNext(GifFile, &Dummy) == GIF_ERROR)
                {
                    WARN("GIF is not properly terminated\n");
                    break;
                }
            while (Dummy != NULL) ;
        }
        return GIF_OK;
    } else
        return GIF_ERROR;
}