#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ format; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  TYPE_1__ GpBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_ContainerFormatBmp ; 
 scalar_t__ Ok ; 
 scalar_t__ PixelFormat32bppARGB ; 
 scalar_t__ PixelFormat32bppRGB ; 
 scalar_t__ decode_image_wic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static GpStatus decode_image_bmp(IStream* stream, GpImage **image)
{
    GpStatus status;
    GpBitmap* bitmap;

    status = decode_image_wic(stream, &GUID_ContainerFormatBmp, NULL, image);

    bitmap = (GpBitmap*)*image;

    if (status == Ok && bitmap->format == PixelFormat32bppARGB)
    {
        /* WIC supports bmp files with alpha, but gdiplus does not */
        bitmap->format = PixelFormat32bppRGB;
    }

    return status;
}