#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* metadata_reader_func ) (TYPE_1__*,int /*<<< orphan*/ *,int) ;
struct TYPE_21__ {int Width; int Height; int Y; scalar_t__ X; } ;
typedef  TYPE_2__ WICRect ;
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  int /*<<< orphan*/  WICBitmapPaletteType ;
typedef  int UINT ;
struct TYPE_25__ {int /*<<< orphan*/  palette_type; int /*<<< orphan*/  gdip_format; int /*<<< orphan*/ * wic_format; } ;
struct TYPE_24__ {int Stride; scalar_t__ Scan0; } ;
struct TYPE_23__ {scalar_t__ Flags; } ;
struct TYPE_22__ {double xres; double yres; int flags; int frame_count; int current_frame; TYPE_5__* palette; int /*<<< orphan*/ * decoder; } ;
struct TYPE_20__ {TYPE_3__ image; int /*<<< orphan*/ * metadata_reader; } ;
typedef  int /*<<< orphan*/  PixelFormat ;
typedef  int /*<<< orphan*/  IWICMetadataBlockReader ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  IWICBitmapFrameDecode ;
typedef  int /*<<< orphan*/  IWICBitmapDecoder ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ GpStatus ;
typedef  TYPE_3__ GpImage ;
typedef  TYPE_1__ GpBitmap ;
typedef  TYPE_5__ ColorPalette ;
typedef  TYPE_6__ BitmapData ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GUID_WICPixelFormat16bppGray ; 
 int /*<<< orphan*/  GUID_WICPixelFormat2bppGray ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGRA ; 
 int /*<<< orphan*/  GUID_WICPixelFormat4bppGray ; 
 int /*<<< orphan*/  GUID_WICPixelFormat8bppGray ; 
 int /*<<< orphan*/  GUID_WICPixelFormatBlackWhite ; 
 scalar_t__ GdipBitmapLockBits (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  GdipBitmapUnlockBits (TYPE_1__*,TYPE_6__*) ; 
 scalar_t__ GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  GdipDisposeImage (TYPE_3__*) ; 
 int /*<<< orphan*/  IID_IWICMetadataBlockReader ; 
 int /*<<< orphan*/  IWICBitmapDecoder_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapDecoder_GetFrame (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_GetFrameCount (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ IWICBitmapFrameDecode_GetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapFrameDecode_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IWICBitmapFrameDecode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_AddRef (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapSource_CopyPixels (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICBitmapSource_GetResolution (int /*<<< orphan*/ *,double*,double*) ; 
 scalar_t__ IWICBitmapSource_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IWICBitmapSource_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWICMetadataBlockReader_GetCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICMetadataBlockReader_GetReaderByIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICMetadataBlockReader_Release (int /*<<< orphan*/ *) ; 
 int ImageFlagsColorSpaceGRAY ; 
 int ImageFlagsColorSpaceRGB ; 
 int ImageFlagsHasRealDPI ; 
 int ImageFlagsHasRealPixelSize ; 
 int ImageFlagsReadOnly ; 
 int /*<<< orphan*/  ImageLockModeWrite ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,...) ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeFixedHalftone256 ; 
 scalar_t__ WICConvertBitmapSource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  abs (int) ; 
 TYPE_5__* get_palette (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_5__*) ; 
 scalar_t__ hresult_to_status (scalar_t__) ; 
 TYPE_7__* pixel_formats ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GpStatus decode_frame_wic(IWICBitmapDecoder *decoder, BOOL force_conversion,
    UINT active_frame, metadata_reader_func metadata_reader, GpImage **image)
{
    GpStatus status=Ok;
    GpBitmap *bitmap;
    HRESULT hr;
    IWICBitmapFrameDecode *frame;
    IWICBitmapSource *source=NULL;
    IWICMetadataBlockReader *block_reader;
    WICPixelFormatGUID wic_format;
    PixelFormat gdip_format=0;
    ColorPalette *palette = NULL;
    WICBitmapPaletteType palette_type = WICBitmapPaletteTypeFixedHalftone256;
    int i;
    UINT width, height, frame_count;
    BitmapData lockeddata;
    WICRect wrc;

    TRACE("%p,%u,%p\n", decoder, active_frame, image);

    IWICBitmapDecoder_GetFrameCount(decoder, &frame_count);
    hr = IWICBitmapDecoder_GetFrame(decoder, active_frame, &frame);
    if (SUCCEEDED(hr)) /* got frame */
    {
        hr = IWICBitmapFrameDecode_GetPixelFormat(frame, &wic_format);

        if (SUCCEEDED(hr))
        {
            if (!force_conversion)
            {
                for (i=0; pixel_formats[i].wic_format; i++)
                {
                    if (IsEqualGUID(&wic_format, pixel_formats[i].wic_format))
                    {
                        source = (IWICBitmapSource*)frame;
                        IWICBitmapSource_AddRef(source);
                        gdip_format = pixel_formats[i].gdip_format;
                        palette_type = pixel_formats[i].palette_type;
                        break;
                    }
                }
            }
            if (!source)
            {
                /* unknown format; fall back on 32bppARGB */
                hr = WICConvertBitmapSource(&GUID_WICPixelFormat32bppBGRA, (IWICBitmapSource*)frame, &source);
                gdip_format = PixelFormat32bppARGB;
            }
            TRACE("%s => %#x\n", wine_dbgstr_guid(&wic_format), gdip_format);
        }

        if (SUCCEEDED(hr)) /* got source */
        {
            hr = IWICBitmapSource_GetSize(source, &width, &height);

            if (SUCCEEDED(hr))
                status = GdipCreateBitmapFromScan0(width, height, 0, gdip_format,
                    NULL, &bitmap);

            if (SUCCEEDED(hr) && status == Ok) /* created bitmap */
            {
                status = GdipBitmapLockBits(bitmap, NULL, ImageLockModeWrite,
                    gdip_format, &lockeddata);
                if (status == Ok) /* locked bitmap */
                {
                    wrc.X = 0;
                    wrc.Width = width;
                    wrc.Height = 1;
                    for (i=0; i<height; i++)
                    {
                        wrc.Y = i;
                        hr = IWICBitmapSource_CopyPixels(source, &wrc, abs(lockeddata.Stride),
                            abs(lockeddata.Stride), (BYTE*)lockeddata.Scan0+lockeddata.Stride*i);
                        if (FAILED(hr)) break;
                    }

                    GdipBitmapUnlockBits(bitmap, &lockeddata);
                }

                if (SUCCEEDED(hr) && status == Ok)
                    *image = &bitmap->image;
                else
                {
                    *image = NULL;
                    GdipDisposeImage(&bitmap->image);
                }

                if (SUCCEEDED(hr) && status == Ok)
                {
                    double dpix, dpiy;
                    hr = IWICBitmapSource_GetResolution(source, &dpix, &dpiy);
                    if (SUCCEEDED(hr))
                    {
                        bitmap->image.xres = dpix;
                        bitmap->image.yres = dpiy;
                    }
                    hr = S_OK;
                }
            }

            IWICBitmapSource_Release(source);
        }

        if (SUCCEEDED(hr)) {
            bitmap->metadata_reader = NULL;

            if (metadata_reader)
                metadata_reader(bitmap, decoder, active_frame);
            else if (IWICBitmapFrameDecode_QueryInterface(frame, &IID_IWICMetadataBlockReader, (void **)&block_reader) == S_OK)
            {
                UINT block_count = 0;
                if (IWICMetadataBlockReader_GetCount(block_reader, &block_count) == S_OK && block_count)
                    IWICMetadataBlockReader_GetReaderByIndex(block_reader, 0, &bitmap->metadata_reader);
                IWICMetadataBlockReader_Release(block_reader);
            }

            palette = get_palette(frame, palette_type);
            IWICBitmapFrameDecode_Release(frame);
        }
    }

    if (FAILED(hr) && status == Ok) status = hresult_to_status(hr);

    if (status == Ok)
    {
        /* Native GDI+ used to be smarter, but since Win7 it just sets these flags. */
        bitmap->image.flags |= ImageFlagsReadOnly|ImageFlagsHasRealPixelSize|ImageFlagsHasRealDPI;
        if (IsEqualGUID(&wic_format, &GUID_WICPixelFormat2bppGray) ||
            IsEqualGUID(&wic_format, &GUID_WICPixelFormat4bppGray) ||
            IsEqualGUID(&wic_format, &GUID_WICPixelFormat8bppGray) ||
            IsEqualGUID(&wic_format, &GUID_WICPixelFormat16bppGray))
            bitmap->image.flags |= ImageFlagsColorSpaceGRAY;
        else
            bitmap->image.flags |= ImageFlagsColorSpaceRGB;
        bitmap->image.frame_count = frame_count;
        bitmap->image.current_frame = active_frame;
        bitmap->image.decoder = decoder;
        IWICBitmapDecoder_AddRef(decoder);
        if (palette)
        {
            heap_free(bitmap->image.palette);
            bitmap->image.palette = palette;
        }
        else
        {
            if (IsEqualGUID(&wic_format, &GUID_WICPixelFormatBlackWhite))
                bitmap->image.palette->Flags = 0;
        }
        TRACE("=> %p\n", *image);
    }

    return status;
}