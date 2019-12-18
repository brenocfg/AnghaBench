#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  format; int /*<<< orphan*/  busy; int /*<<< orphan*/  decoder; } ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  TYPE_1__ GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ImageTypeBitmap ; 
 scalar_t__ ImageTypeMetafile ; 
 scalar_t__ Ok ; 
 scalar_t__ decode_frame_wic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  free_image_data (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static GpStatus select_frame_wic(GpImage *image, UINT active_frame)
{
    GpImage *new_image;
    GpStatus status;

    status = decode_frame_wic(image->decoder, FALSE, active_frame, NULL, &new_image);
    if(status != Ok)
        return status;

    new_image->busy = image->busy;
    memcpy(&new_image->format, &image->format, sizeof(GUID));
    free_image_data(image);
    if (image->type == ImageTypeBitmap)
        *(GpBitmap *)image = *(GpBitmap *)new_image;
    else if (image->type == ImageTypeMetafile)
        *(GpMetafile *)image = *(GpMetafile *)new_image;
    new_image->type = ~0;
    heap_free(new_image);
    return Ok;
}