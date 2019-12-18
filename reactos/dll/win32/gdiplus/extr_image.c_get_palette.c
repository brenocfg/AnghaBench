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
typedef  int WICBitmapPaletteType ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Count; int /*<<< orphan*/  Entries; } ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int /*<<< orphan*/  IWICImagingFactory ;
typedef  int /*<<< orphan*/  IWICBitmapFrameDecode ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ ColorPalette ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IWICBitmapFrameDecode_CopyPalette (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IWICImagingFactory_CreatePalette (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICImagingFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICPalette_GetColorCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPalette_GetColors (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICPalette_GetType (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPalette_HasAlpha (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IWICPalette_InitializePredefined (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PaletteFlagsGrayScale ; 
 int /*<<< orphan*/  PaletteFlagsHalftone ; 
 int /*<<< orphan*/  PaletteFlagsHasAlpha ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
#define  WICBitmapPaletteTypeFixedGray16 137 
#define  WICBitmapPaletteTypeFixedGray256 136 
#define  WICBitmapPaletteTypeFixedGray4 135 
#define  WICBitmapPaletteTypeFixedHalftone125 134 
#define  WICBitmapPaletteTypeFixedHalftone216 133 
#define  WICBitmapPaletteTypeFixedHalftone252 132 
#define  WICBitmapPaletteTypeFixedHalftone256 131 
#define  WICBitmapPaletteTypeFixedHalftone27 130 
#define  WICBitmapPaletteTypeFixedHalftone64 129 
#define  WICBitmapPaletteTypeFixedHalftone8 128 
 scalar_t__ WICCreateImagingFactory_Proxy (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ WINCODEC_ERR_PALETTEUNAVAILABLE ; 
 int /*<<< orphan*/  WINCODEC_SDK_VERSION ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static ColorPalette *get_palette(IWICBitmapFrameDecode *frame, WICBitmapPaletteType palette_type)
{
    HRESULT hr;
    IWICImagingFactory *factory;
    IWICPalette *wic_palette;
    ColorPalette *palette = NULL;

    hr = WICCreateImagingFactory_Proxy(WINCODEC_SDK_VERSION, &factory);
    if (hr != S_OK) return NULL;

    hr = IWICImagingFactory_CreatePalette(factory, &wic_palette);
    if (hr == S_OK)
    {
        hr = WINCODEC_ERR_PALETTEUNAVAILABLE;
        if (frame)
            hr = IWICBitmapFrameDecode_CopyPalette(frame, wic_palette);
        if (hr != S_OK)
        {
            TRACE("using predefined palette %#x\n", palette_type);
            hr = IWICPalette_InitializePredefined(wic_palette, palette_type, FALSE);
        }
        if (hr == S_OK)
        {
            WICBitmapPaletteType type;
            BOOL alpha;
            UINT count;

            IWICPalette_GetColorCount(wic_palette, &count);
            palette = heap_alloc(2 * sizeof(UINT) + count * sizeof(ARGB));
            IWICPalette_GetColors(wic_palette, count, palette->Entries, &palette->Count);

            IWICPalette_GetType(wic_palette, &type);
            switch(type) {
                case WICBitmapPaletteTypeFixedGray4:
                case WICBitmapPaletteTypeFixedGray16:
                case WICBitmapPaletteTypeFixedGray256:
                    palette->Flags = PaletteFlagsGrayScale;
                    break;
                case WICBitmapPaletteTypeFixedHalftone8:
                case WICBitmapPaletteTypeFixedHalftone27:
                case WICBitmapPaletteTypeFixedHalftone64:
                case WICBitmapPaletteTypeFixedHalftone125:
                case WICBitmapPaletteTypeFixedHalftone216:
                case WICBitmapPaletteTypeFixedHalftone252:
                case WICBitmapPaletteTypeFixedHalftone256:
                    palette->Flags = PaletteFlagsHalftone;
                    break;
                default:
                    palette->Flags = 0;
            }
            IWICPalette_HasAlpha(wic_palette, &alpha);
            if(alpha)
                palette->Flags |= PaletteFlagsHasAlpha;
        }
        IWICPalette_Release(wic_palette);
    }
    IWICImagingFactory_Release(factory);
    return palette;
}