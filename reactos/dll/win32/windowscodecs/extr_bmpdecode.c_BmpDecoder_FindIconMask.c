#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_3__ {scalar_t__ read_data_func; int bitsperpixel; int image_offset; scalar_t__ stride; int /*<<< orphan*/  IWICBitmapFrameDecode_iface; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ BmpDecoder ;

/* Variables and functions */
 scalar_t__ BmpFrameDecode_ReadUncompressed ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void BmpDecoder_FindIconMask(BmpDecoder *This, ULONG *mask_offset, int *topdown)
{
    assert(This->stream != NULL);

    if (This->read_data_func == BmpFrameDecode_ReadUncompressed)
    {
        /* RGB or BITFIELDS data */
        ULONG width, height, bytesperrow, datasize;
        IWICBitmapFrameDecode_GetSize(&This->IWICBitmapFrameDecode_iface, &width, &height);
        bytesperrow = (((width * This->bitsperpixel)+31)/32)*4;
        datasize = bytesperrow * height;
        *mask_offset = This->image_offset + datasize;
    }
    else
        *mask_offset = 0;

    *topdown = This->stride > 0;
}