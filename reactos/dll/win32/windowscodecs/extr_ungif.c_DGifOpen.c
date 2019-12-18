#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* UserData; int /*<<< orphan*/  Read; void* Private; } ;
typedef  int /*<<< orphan*/  InputFunc ;
typedef  TYPE_1__ GifFileType ;
typedef  TYPE_1__ GifFilePrivateType ;

/* Variables and functions */
 scalar_t__ DGifGetScreenDesc (TYPE_1__*) ; 
 scalar_t__ GIF_ERROR ; 
 int /*<<< orphan*/  GIF_STAMP ; 
 int GIF_STAMP_LEN ; 
 int /*<<< orphan*/  GIF_VERSION_POS ; 
 int READ (TYPE_1__*,unsigned char*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 TYPE_1__* ungif_alloc (int) ; 
 int /*<<< orphan*/  ungif_free (TYPE_1__*) ; 

GifFileType *
DGifOpen(void *userData,
         InputFunc readFunc) {

    unsigned char Buf[GIF_STAMP_LEN + 1];
    GifFileType *GifFile;
    GifFilePrivateType *Private;

    GifFile = ungif_alloc(sizeof(GifFileType));
    if (GifFile == NULL) {
        return NULL;
    }

    memset(GifFile, '\0', sizeof(GifFileType));

    Private = ungif_alloc(sizeof(GifFilePrivateType));
    if (!Private) {
        ungif_free(GifFile);
        return NULL;
    }

    GifFile->Private = (void*)Private;

    Private->Read = readFunc;    /* TVT */
    GifFile->UserData = userData;    /* TVT */

    /* Lets see if this is a GIF file: */
    if (READ(GifFile, Buf, GIF_STAMP_LEN) != GIF_STAMP_LEN) {
        ungif_free(Private);
        ungif_free(GifFile);
        return NULL;
    }

    /* The GIF Version number is ignored at this time. Maybe we should do
     * something more useful with it. */
    Buf[GIF_STAMP_LEN] = 0;
    if (memcmp(GIF_STAMP, Buf, GIF_VERSION_POS) != 0) {
        ungif_free(Private);
        ungif_free(GifFile);
        return NULL;
    }

    if (DGifGetScreenDesc(GifFile) == GIF_ERROR) {
        ungif_free(Private);
        ungif_free(GifFile);
        return NULL;
    }

    return GifFile;
}