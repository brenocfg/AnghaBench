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
struct TYPE_6__ {int* Buf; } ;
struct TYPE_5__ {TYPE_2__* Private; } ;
typedef  TYPE_1__ GifFileType ;
typedef  TYPE_2__ GifFilePrivateType ;
typedef  int GifByteType ;

/* Variables and functions */
 int GIF_ERROR ; 
 int GIF_OK ; 
 int READ (TYPE_1__*,int*,int) ; 

__attribute__((used)) static int
DGifGetExtensionNext(GifFileType * GifFile,
                     GifByteType ** Extension) {

    GifByteType Buf;
    GifFilePrivateType *Private = GifFile->Private;

    if (READ(GifFile, &Buf, 1) != 1) {
        return GIF_ERROR;
    }
    if (Buf > 0) {
        *Extension = Private->Buf;    /* Use private unused buffer. */
        (*Extension)[0] = Buf;  /* Pascal strings notation (pos. 0 is len.). */
        if (READ(GifFile, &((*Extension)[1]), Buf) != Buf) {
            return GIF_ERROR;
        }
    } else
        *Extension = NULL;

    return GIF_OK;
}