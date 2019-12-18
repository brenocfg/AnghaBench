#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct FormatConverter {int /*<<< orphan*/  source; } ;
typedef  enum pixelformat { ____Placeholder_pixelformat } pixelformat ;
struct TYPE_4__ {int Width; int Height; } ;
typedef  TYPE_1__ WICRect ;
typedef  int UINT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void* BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ ,TYPE_1__ const*,int,int,void**) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WINCODEC_ERR_UNSUPPORTEDOPERATION ; 
#define  format_24bppBGR 132 
#define  format_24bppRGB 131 
#define  format_32bppBGR 130 
#define  format_32bppBGRA 129 
#define  format_32bppPBGRA 128 
 int /*<<< orphan*/  reverse_bgr8 (int,void**,int,int,int) ; 

__attribute__((used)) static HRESULT copypixels_to_24bppRGB(struct FormatConverter *This, const WICRect *prc,
    UINT cbStride, UINT cbBufferSize, BYTE *pbBuffer, enum pixelformat source_format)
{
    HRESULT hr;

    switch (source_format)
    {
    case format_24bppBGR:
    case format_24bppRGB:
        if (prc)
        {
            hr = IWICBitmapSource_CopyPixels(This->source, prc, cbStride, cbBufferSize, pbBuffer);
            if (SUCCEEDED(hr) && source_format == format_24bppBGR)
              reverse_bgr8(3, pbBuffer, prc->Width, prc->Height, cbStride);
            return hr;
        }
        return S_OK;
    case format_32bppBGR:
    case format_32bppBGRA:
    case format_32bppPBGRA:
        if (prc)
        {
            HRESULT res;
            INT x, y;
            BYTE *srcdata;
            UINT srcstride, srcdatasize;
            const BYTE *srcrow;
            const BYTE *srcpixel;
            BYTE *dstrow;
            BYTE *dstpixel;
            BYTE tmppixel[3];

            srcstride = 4 * prc->Width;
            srcdatasize = srcstride * prc->Height;

            srcdata = HeapAlloc(GetProcessHeap(), 0, srcdatasize);
            if (!srcdata) return E_OUTOFMEMORY;

            res = IWICBitmapSource_CopyPixels(This->source, prc, srcstride, srcdatasize, srcdata);

            if (SUCCEEDED(res))
            {
                srcrow = srcdata;
                dstrow = pbBuffer;
                for (y=0; y<prc->Height; y++) {
                    srcpixel=srcrow;
                    dstpixel=dstrow;
                    for (x=0; x<prc->Width; x++) {
                        tmppixel[0]=*srcpixel++; /* blue */
                        tmppixel[1]=*srcpixel++; /* green */
                        tmppixel[2]=*srcpixel++; /* red */
                        srcpixel++; /* alpha */

                        *dstpixel++=tmppixel[2]; /* red */
                        *dstpixel++=tmppixel[1]; /* green */
                        *dstpixel++=tmppixel[0]; /* blue */
                    }
                    srcrow += srcstride;
                    dstrow += cbStride;
                }
            }

            HeapFree(GetProcessHeap(), 0, srcdata);

            return res;
        }
        return S_OK;
    default:
        FIXME("Unimplemented conversion path!\n");
        return WINCODEC_ERR_UNSUPPORTEDOPERATION;
    }
}