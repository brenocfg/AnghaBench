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
struct pixel_format {int /*<<< orphan*/  cDepthBits; int /*<<< orphan*/  cAccumAlphaBits; int /*<<< orphan*/  cAccumBlueBits; int /*<<< orphan*/  cAccumGreenBits; int /*<<< orphan*/  cAccumRedBits; int /*<<< orphan*/  cAccumBits; int /*<<< orphan*/  cAlphaShift; int /*<<< orphan*/  cAlphaBits; int /*<<< orphan*/  cBlueShift; int /*<<< orphan*/  cBlueBits; int /*<<< orphan*/  cGreenShift; int /*<<< orphan*/  cGreenBits; int /*<<< orphan*/  cRedShift; int /*<<< orphan*/  cRedBits; int /*<<< orphan*/  cColorBits; int /*<<< orphan*/  iPixelType; int /*<<< orphan*/  dwFlags; } ;
typedef  int UINT ;
struct TYPE_3__ {int nSize; int nVersion; scalar_t__ dwDamageMask; scalar_t__ dwVisibleMask; scalar_t__ dwLayerMask; scalar_t__ bReserved; int /*<<< orphan*/  iLayerType; scalar_t__ cAuxBuffers; int /*<<< orphan*/  cStencilBits; int /*<<< orphan*/  cDepthBits; int /*<<< orphan*/  cAccumAlphaBits; int /*<<< orphan*/  cAccumBlueBits; int /*<<< orphan*/  cAccumGreenBits; int /*<<< orphan*/  cAccumRedBits; int /*<<< orphan*/  cAccumBits; int /*<<< orphan*/  cAlphaShift; int /*<<< orphan*/  cAlphaBits; int /*<<< orphan*/  cBlueShift; int /*<<< orphan*/  cBlueBits; int /*<<< orphan*/  cGreenShift; int /*<<< orphan*/  cGreenBits; int /*<<< orphan*/  cRedShift; int /*<<< orphan*/  cRedBits; int /*<<< orphan*/  cColorBits; int /*<<< orphan*/  iPixelType; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  PFD_MAIN_PLANE ; 
 int /*<<< orphan*/  STENCIL_BITS ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 struct pixel_format* get_format (scalar_t__,scalar_t__*) ; 

INT sw_DescribePixelFormat(HDC hdc, INT format, UINT size, PIXELFORMATDESCRIPTOR* descr)
{
    INT ret;
    const struct pixel_format *pixel_format;
    
    TRACE("Describing format %i.\n", format);

    pixel_format = get_format(format, &ret);
    if(!descr)
        return ret;
    if((format > ret) || (size != sizeof(*descr)))
        return 0;

    /* Fill the structure */
    descr->nSize            = sizeof(*descr);
    descr->nVersion         = 1;
    descr->dwFlags          = pixel_format->dwFlags;
    descr->iPixelType       = pixel_format->iPixelType;
    descr->cColorBits       = pixel_format->cColorBits;
    descr->cRedBits         = pixel_format->cRedBits;
    descr->cRedShift        = pixel_format->cRedShift;
    descr->cGreenBits       = pixel_format->cGreenBits;
    descr->cGreenShift      = pixel_format->cGreenShift;
    descr->cBlueBits        = pixel_format->cBlueBits;
    descr->cBlueShift       = pixel_format->cBlueShift;
    descr->cAlphaBits       = pixel_format->cAlphaBits;
    descr->cAlphaShift      = pixel_format->cAlphaShift;
    descr->cAccumBits       = pixel_format->cAccumBits;
    descr->cAccumRedBits    = pixel_format->cAccumRedBits;
    descr->cAccumGreenBits  = pixel_format->cAccumGreenBits;
    descr->cAccumBlueBits   = pixel_format->cAccumBlueBits;
    descr->cAccumAlphaBits  = pixel_format->cAccumAlphaBits;
    descr->cDepthBits       = pixel_format->cDepthBits;
    descr->cStencilBits     = STENCIL_BITS;
    descr->cAuxBuffers      = 0;
    descr->iLayerType       = PFD_MAIN_PLANE;
    descr->bReserved        = 0;
    descr->dwLayerMask      = 0;
    descr->dwVisibleMask    = 0;
    descr->dwDamageMask     = 0;

    return ret;
}