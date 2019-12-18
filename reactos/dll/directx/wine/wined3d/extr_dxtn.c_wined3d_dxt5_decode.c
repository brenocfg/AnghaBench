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
typedef  enum wined3d_format_id { ____Placeholder_wined3d_format_id } wined3d_format_id ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  WINED3DFMT_B8G8R8A8_UNORM 129 
#define  WINED3DFMT_B8G8R8X8_UNORM 128 
 int /*<<< orphan*/  debug_d3dformat (int) ; 
 int /*<<< orphan*/  dxt5_to_x8r8g8b8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txc_dxtn_handle ; 

BOOL wined3d_dxt5_decode(const BYTE *src, BYTE *dst, DWORD pitch_in, DWORD pitch_out,
        enum wined3d_format_id format, unsigned int w, unsigned int h)
{
    if (!txc_dxtn_handle)
        return FALSE;

    switch (format)
    {
        case WINED3DFMT_B8G8R8A8_UNORM:
            return dxt5_to_x8r8g8b8(src, dst, pitch_in, pitch_out, w, h, TRUE);
        case WINED3DFMT_B8G8R8X8_UNORM:
            return dxt5_to_x8r8g8b8(src, dst, pitch_in, pitch_out, w, h, FALSE);
        default:
            break;
    }

    FIXME("Cannot find a conversion function from format DXT5 to %s.\n", debug_d3dformat(format));
    return FALSE;
}