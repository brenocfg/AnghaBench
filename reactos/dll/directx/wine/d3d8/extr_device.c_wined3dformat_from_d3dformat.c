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
typedef  int D3DFORMAT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  D3DFMT_A1R5G5B5 162 
#define  D3DFMT_A2B10G10R10 161 
#define  D3DFMT_A2W10V10U10 160 
#define  D3DFMT_A4L4 159 
#define  D3DFMT_A4R4G4B4 158 
#define  D3DFMT_A8 157 
#define  D3DFMT_A8L8 156 
#define  D3DFMT_A8P8 155 
#define  D3DFMT_A8R3G3B2 154 
#define  D3DFMT_A8R8G8B8 153 
#define  D3DFMT_D15S1 152 
#define  D3DFMT_D16 151 
#define  D3DFMT_D16_LOCKABLE 150 
#define  D3DFMT_D24S8 149 
#define  D3DFMT_D24X4S4 148 
#define  D3DFMT_D24X8 147 
#define  D3DFMT_D32 146 
#define  D3DFMT_G16R16 145 
#define  D3DFMT_INDEX16 144 
#define  D3DFMT_INDEX32 143 
#define  D3DFMT_L6V5U5 142 
#define  D3DFMT_L8 141 
#define  D3DFMT_P8 140 
#define  D3DFMT_Q8W8V8U8 139 
#define  D3DFMT_R3G3B2 138 
#define  D3DFMT_R5G6B5 137 
#define  D3DFMT_R8G8B8 136 
#define  D3DFMT_UNKNOWN 135 
#define  D3DFMT_V16U16 134 
#define  D3DFMT_V8U8 133 
#define  D3DFMT_W11V11U10 132 
#define  D3DFMT_X1R5G5B5 131 
#define  D3DFMT_X4R4G4B4 130 
#define  D3DFMT_X8L8V8U8 129 
#define  D3DFMT_X8R8G8B8 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int WINED3DFMT_A8_UNORM ; 
 int WINED3DFMT_B2G3R3A8_UNORM ; 
 int WINED3DFMT_B2G3R3_UNORM ; 
 int WINED3DFMT_B4G4R4A4_UNORM ; 
 int WINED3DFMT_B4G4R4X4_UNORM ; 
 int WINED3DFMT_B5G5R5A1_UNORM ; 
 int WINED3DFMT_B5G5R5X1_UNORM ; 
 int WINED3DFMT_B5G6R5_UNORM ; 
 int WINED3DFMT_B8G8R8A8_UNORM ; 
 int WINED3DFMT_B8G8R8X8_UNORM ; 
 int WINED3DFMT_B8G8R8_UNORM ; 
 int WINED3DFMT_D16_LOCKABLE ; 
 int WINED3DFMT_D16_UNORM ; 
 int WINED3DFMT_D24_UNORM_S8_UINT ; 
 int WINED3DFMT_D32_UNORM ; 
 int WINED3DFMT_L4A4_UNORM ; 
 int WINED3DFMT_L8A8_UNORM ; 
 int WINED3DFMT_L8_UNORM ; 
 int WINED3DFMT_P8_UINT ; 
 int WINED3DFMT_P8_UINT_A8_UNORM ; 
 int WINED3DFMT_R10G10B10A2_UNORM ; 
 int WINED3DFMT_R10G10B10_SNORM_A2_UNORM ; 
 int WINED3DFMT_R10G11B11_SNORM ; 
 int WINED3DFMT_R16G16_SNORM ; 
 int WINED3DFMT_R16G16_UNORM ; 
 int WINED3DFMT_R16_UINT ; 
 int WINED3DFMT_R32_UINT ; 
 int WINED3DFMT_R5G5_SNORM_L6_UNORM ; 
 int WINED3DFMT_R8G8B8A8_SNORM ; 
 int WINED3DFMT_R8G8_SNORM ; 
 int WINED3DFMT_R8G8_SNORM_L8X8_UNORM ; 
 int WINED3DFMT_S1_UINT_D15_UNORM ; 
 int WINED3DFMT_S4X4_UINT_D24_UNORM ; 
 int WINED3DFMT_UNKNOWN ; 
 int WINED3DFMT_X8D24_UNORM ; 
 scalar_t__ isprint (int /*<<< orphan*/ ) ; 

enum wined3d_format_id wined3dformat_from_d3dformat(D3DFORMAT format)
{
    BYTE *c = (BYTE *)&format;

    /* Don't translate FOURCC formats */
    if (isprint(c[0]) && isprint(c[1]) && isprint(c[2]) && isprint(c[3])) return format;

    switch(format)
    {
        case D3DFMT_UNKNOWN: return WINED3DFMT_UNKNOWN;
        case D3DFMT_R8G8B8: return WINED3DFMT_B8G8R8_UNORM;
        case D3DFMT_A8R8G8B8: return WINED3DFMT_B8G8R8A8_UNORM;
        case D3DFMT_X8R8G8B8: return WINED3DFMT_B8G8R8X8_UNORM;
        case D3DFMT_R5G6B5: return WINED3DFMT_B5G6R5_UNORM;
        case D3DFMT_X1R5G5B5: return WINED3DFMT_B5G5R5X1_UNORM;
        case D3DFMT_A1R5G5B5: return WINED3DFMT_B5G5R5A1_UNORM;
        case D3DFMT_A4R4G4B4: return WINED3DFMT_B4G4R4A4_UNORM;
        case D3DFMT_R3G3B2: return WINED3DFMT_B2G3R3_UNORM;
        case D3DFMT_A8: return WINED3DFMT_A8_UNORM;
        case D3DFMT_A8R3G3B2: return WINED3DFMT_B2G3R3A8_UNORM;
        case D3DFMT_X4R4G4B4: return WINED3DFMT_B4G4R4X4_UNORM;
        case D3DFMT_A2B10G10R10: return WINED3DFMT_R10G10B10A2_UNORM;
        case D3DFMT_G16R16: return WINED3DFMT_R16G16_UNORM;
        case D3DFMT_A8P8: return WINED3DFMT_P8_UINT_A8_UNORM;
        case D3DFMT_P8: return WINED3DFMT_P8_UINT;
        case D3DFMT_L8: return WINED3DFMT_L8_UNORM;
        case D3DFMT_A8L8: return WINED3DFMT_L8A8_UNORM;
        case D3DFMT_A4L4: return WINED3DFMT_L4A4_UNORM;
        case D3DFMT_V8U8: return WINED3DFMT_R8G8_SNORM;
        case D3DFMT_L6V5U5: return WINED3DFMT_R5G5_SNORM_L6_UNORM;
        case D3DFMT_X8L8V8U8: return WINED3DFMT_R8G8_SNORM_L8X8_UNORM;
        case D3DFMT_Q8W8V8U8: return WINED3DFMT_R8G8B8A8_SNORM;
        case D3DFMT_V16U16: return WINED3DFMT_R16G16_SNORM;
        case D3DFMT_W11V11U10: return WINED3DFMT_R10G11B11_SNORM;
        case D3DFMT_A2W10V10U10: return WINED3DFMT_R10G10B10_SNORM_A2_UNORM;
        case D3DFMT_D16_LOCKABLE: return WINED3DFMT_D16_LOCKABLE;
        case D3DFMT_D32: return WINED3DFMT_D32_UNORM;
        case D3DFMT_D15S1: return WINED3DFMT_S1_UINT_D15_UNORM;
        case D3DFMT_D24S8: return WINED3DFMT_D24_UNORM_S8_UINT;
        case D3DFMT_D24X8: return WINED3DFMT_X8D24_UNORM;
        case D3DFMT_D24X4S4: return WINED3DFMT_S4X4_UINT_D24_UNORM;
        case D3DFMT_D16: return WINED3DFMT_D16_UNORM;
        case D3DFMT_INDEX16: return WINED3DFMT_R16_UINT;
        case D3DFMT_INDEX32: return WINED3DFMT_R32_UINT;
        default:
            FIXME("Unhandled D3DFORMAT %#x.\n", format);
            return WINED3DFMT_UNKNOWN;
    }
}