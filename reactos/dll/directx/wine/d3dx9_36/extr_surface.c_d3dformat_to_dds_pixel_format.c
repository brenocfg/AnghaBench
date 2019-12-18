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
struct dds_pixel_format {int size; scalar_t__ fourcc; int /*<<< orphan*/  flags; int /*<<< orphan*/  amask; int /*<<< orphan*/  bmask; int /*<<< orphan*/  gmask; int /*<<< orphan*/  rmask; int /*<<< orphan*/  bpp; } ;
struct TYPE_3__ {scalar_t__ format; int /*<<< orphan*/  amask; int /*<<< orphan*/  bmask; int /*<<< orphan*/  gmask; int /*<<< orphan*/  rmask; int /*<<< orphan*/  bpp; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ D3DFORMAT ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ D3DFMT_UNKNOWN ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  DDS_PF_ALPHA ; 
 int /*<<< orphan*/  DDS_PF_FOURCC ; 
 int /*<<< orphan*/  DDS_PF_RGB ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 scalar_t__ dds_fourcc_to_d3dformat (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct dds_pixel_format*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* rgb_pixel_formats ; 

__attribute__((used)) static HRESULT d3dformat_to_dds_pixel_format(struct dds_pixel_format *pixel_format, D3DFORMAT d3dformat)
{
    unsigned int i;

    memset(pixel_format, 0, sizeof(*pixel_format));

    pixel_format->size = sizeof(*pixel_format);

    for (i = 0; i < ARRAY_SIZE(rgb_pixel_formats); i++)
    {
        if (rgb_pixel_formats[i].format == d3dformat)
        {
            pixel_format->flags |= DDS_PF_RGB;
            pixel_format->bpp = rgb_pixel_formats[i].bpp;
            pixel_format->rmask = rgb_pixel_formats[i].rmask;
            pixel_format->gmask = rgb_pixel_formats[i].gmask;
            pixel_format->bmask = rgb_pixel_formats[i].bmask;
            pixel_format->amask = rgb_pixel_formats[i].amask;
            if (pixel_format->amask) pixel_format->flags |= DDS_PF_ALPHA;
            return D3D_OK;
        }
    }

    /* Reuse dds_fourcc_to_d3dformat as D3DFORMAT and FOURCC are DWORD with same values */
    if (dds_fourcc_to_d3dformat(d3dformat) != D3DFMT_UNKNOWN)
    {
        pixel_format->flags |= DDS_PF_FOURCC;
        pixel_format->fourcc = d3dformat;
        return D3D_OK;
    }

    WARN("Unknown pixel format %#x\n", d3dformat);
    return E_NOTIMPL;
}