#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dds_pixel_format {int bpp; int rmask; int gmask; int bmask; int /*<<< orphan*/  amask; } ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DFMT_UNKNOWN ; 
 int /*<<< orphan*/  D3DFMT_X8L8V8U8 ; 
 int /*<<< orphan*/  WARN (char*,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static D3DFORMAT dds_bump_luminance_to_d3dformat(const struct dds_pixel_format *pixel_format)
{
    if (pixel_format->bpp == 32 && pixel_format->rmask == 0x000000ff && pixel_format->gmask == 0x0000ff00
            && pixel_format->bmask == 0x00ff0000)
        return D3DFMT_X8L8V8U8;

    WARN("Unknown bump pixel format (%u, %#x, %#x, %#x, %#x)\n", pixel_format->bpp,
        pixel_format->rmask, pixel_format->gmask, pixel_format->bmask, pixel_format->amask);
    return D3DFMT_UNKNOWN;
}