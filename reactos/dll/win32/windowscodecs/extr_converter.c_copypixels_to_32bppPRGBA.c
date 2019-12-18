#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct FormatConverter {int /*<<< orphan*/  source; } ;
typedef  enum pixelformat { ____Placeholder_pixelformat } pixelformat ;
struct TYPE_5__ {int Height; int Width; } ;
typedef  TYPE_1__ WICRect ;
typedef  int UINT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ ,TYPE_1__ const*,int,int,int*) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  copypixels_to_32bppRGBA (struct FormatConverter*,TYPE_1__ const*,int,int,int*,int) ; 
#define  format_32bppPRGBA 128 

__attribute__((used)) static HRESULT copypixels_to_32bppPRGBA(struct FormatConverter *This, const WICRect *prc,
    UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer, enum pixelformat source_format)
{
    HRESULT hr;

    switch (source_format)
    {
    case format_32bppPRGBA:
        if (prc)
            return IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
        return S_OK;
    default:
        hr = copypixels_to_32bppRGBA(This, prc, cbStride, cbBufferSize, pbBuffer, source_format);
        if (SUCCEEDED(hr) && prc)
        {
            INT x, y;

            for (y=0; y<prc->Height; y++)
                for (x=0; x<prc->Width; x++)
                {
                    BYTE alpha = pbBuffer[cbStride*y+4*x+3];
                    if (alpha != 255)
                    {
                        pbBuffer[cbStride*y+4*x] = pbBuffer[cbStride*y+4*x] * alpha / 255;
                        pbBuffer[cbStride*y+4*x+1] = pbBuffer[cbStride*y+4*x+1] * alpha / 255;
                        pbBuffer[cbStride*y+4*x+2] = pbBuffer[cbStride*y+4*x+2] * alpha / 255;
                    }
                }
        }
        return hr;
    }
}