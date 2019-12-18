#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ColorMap; } ;
struct TYPE_8__ {int /*<<< orphan*/  Extensions; int /*<<< orphan*/ * SavedImages; int /*<<< orphan*/ * SColorMap; TYPE_1__ Image; struct TYPE_8__* Private; } ;
typedef  TYPE_2__ GifFileType ;
typedef  TYPE_2__ GifFilePrivateType ;

/* Variables and functions */
 int /*<<< orphan*/  FreeExtension (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeMapObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeSavedImages (TYPE_2__*) ; 
 int GIF_ERROR ; 
 int GIF_OK ; 
 int /*<<< orphan*/  ungif_free (TYPE_2__*) ; 

int
DGifCloseFile(GifFileType * GifFile) {

    GifFilePrivateType *Private;

    if (GifFile == NULL)
        return GIF_ERROR;

    Private = GifFile->Private;

    if (GifFile->Image.ColorMap) {
        FreeMapObject(GifFile->Image.ColorMap);
        GifFile->Image.ColorMap = NULL;
    }

    if (GifFile->SColorMap) {
        FreeMapObject(GifFile->SColorMap);
        GifFile->SColorMap = NULL;
    }

    ungif_free(Private);
    Private = NULL;

    if (GifFile->SavedImages) {
        FreeSavedImages(GifFile);
        GifFile->SavedImages = NULL;
    }

    FreeExtension(&GifFile->Extensions);

    ungif_free(GifFile);

    return GIF_OK;
}