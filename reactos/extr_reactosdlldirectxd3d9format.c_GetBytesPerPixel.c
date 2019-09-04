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
typedef  int DWORD ;
typedef  int D3DFORMAT ;

/* Variables and functions */
#define  D3DFMT_A16B16G16R16 187 
#define  D3DFMT_A16B16G16R16F 186 
#define  D3DFMT_A1R5G5B5 185 
#define  D3DFMT_A2B10G10R10 184 
#define  D3DFMT_A2R10G10B10 183 
#define  D3DFMT_A2W10V10U10 182 
#define  D3DFMT_A32B32G32R32F 181 
#define  D3DFMT_A4L4 180 
#define  D3DFMT_A4R4G4B4 179 
#define  D3DFMT_A8 178 
#define  D3DFMT_A8B8G8R8 177 
#define  D3DFMT_A8L8 176 
#define  D3DFMT_A8P8 175 
#define  D3DFMT_A8R3G3B2 174 
#define  D3DFMT_A8R8G8B8 173 
#define  D3DFMT_CxV8U8 172 
#define  D3DFMT_D15S1 171 
#define  D3DFMT_D16 170 
#define  D3DFMT_D16_LOCKABLE 169 
#define  D3DFMT_D24FS8 168 
#define  D3DFMT_D24S8 167 
#define  D3DFMT_D24X4S4 166 
#define  D3DFMT_D24X8 165 
#define  D3DFMT_D32 164 
#define  D3DFMT_D32F_LOCKABLE 163 
#define  D3DFMT_D32_LOCKABLE 162 
#define  D3DFMT_DXT1 161 
#define  D3DFMT_DXT2 160 
#define  D3DFMT_DXT3 159 
#define  D3DFMT_DXT4 158 
#define  D3DFMT_DXT5 157 
#define  D3DFMT_G16R16 156 
#define  D3DFMT_G16R16F 155 
#define  D3DFMT_G32R32F 154 
#define  D3DFMT_G8R8_G8B8 153 
#define  D3DFMT_INDEX16 152 
#define  D3DFMT_INDEX32 151 
#define  D3DFMT_L16 150 
#define  D3DFMT_L6V5U5 149 
#define  D3DFMT_L8 148 
#define  D3DFMT_MULTI2_ARGB8 147 
#define  D3DFMT_P8 146 
#define  D3DFMT_Q16W16V16U16 145 
#define  D3DFMT_Q8W8V8U8 144 
#define  D3DFMT_R16F 143 
#define  D3DFMT_R32F 142 
#define  D3DFMT_R3G3B2 141 
#define  D3DFMT_R5G6B5 140 
#define  D3DFMT_R8G8B8 139 
#define  D3DFMT_R8G8_B8G8 138 
#define  D3DFMT_S8_LOCKABLE 137 
#define  D3DFMT_UYVY 136 
#define  D3DFMT_V16U16 135 
#define  D3DFMT_V8U8 134 
#define  D3DFMT_X1R5G5B5 133 
#define  D3DFMT_X4R4G4B4 132 
#define  D3DFMT_X8B8G8R8 131 
#define  D3DFMT_X8L8V8U8 130 
#define  D3DFMT_X8R8G8B8 129 
#define  D3DFMT_YUY2 128 

DWORD GetBytesPerPixel(D3DFORMAT Format)
{
    switch (Format)
    {
    case D3DFMT_R3G3B2:
    case D3DFMT_A8:
        return 1;

    case D3DFMT_R5G6B5:
    case D3DFMT_X1R5G5B5:
    case D3DFMT_A1R5G5B5:
    case D3DFMT_A4R4G4B4:
    case D3DFMT_A8R3G3B2:
    case D3DFMT_X4R4G4B4:
        return 2;

    case D3DFMT_R8G8B8:
        return 3;

    case D3DFMT_A8R8G8B8:
    case D3DFMT_X8R8G8B8:
    case D3DFMT_A2B10G10R10:
    case D3DFMT_A8B8G8R8:
    case D3DFMT_X8B8G8R8:
    case D3DFMT_G16R16:
    case D3DFMT_A2R10G10B10:
        return 4;

    case D3DFMT_A16B16G16R16:
        return 8;


    case D3DFMT_P8:
    case D3DFMT_L8:
    case D3DFMT_A4L4:
        return 1;

    case D3DFMT_A8P8:
    case D3DFMT_A8L8:
        return 2;


    case D3DFMT_V8U8:
    case D3DFMT_L6V5U5:
        return 2;

    case D3DFMT_X8L8V8U8:
    case D3DFMT_Q8W8V8U8:
    case D3DFMT_V16U16:
    case D3DFMT_A2W10V10U10:
        return 4;


    case D3DFMT_S8_LOCKABLE:
        return 1;

    case D3DFMT_D16_LOCKABLE:
    case D3DFMT_D15S1:
    case D3DFMT_D16:
        return 2;

    case D3DFMT_D32:
    case D3DFMT_D24S8:
    case D3DFMT_D24X8:
    case D3DFMT_D24X4S4:
    case D3DFMT_D32F_LOCKABLE:
    case D3DFMT_D24FS8:
    case D3DFMT_D32_LOCKABLE:
        return 4;


    case D3DFMT_L16:
        return 2;

    /* TODO: Handle D3DFMT_VERTEXDATA? */
    case D3DFMT_INDEX16:
        return 2;
    case D3DFMT_INDEX32:
        return 4;


    case D3DFMT_Q16W16V16U16:
        return 8;


    case D3DFMT_R16F:
        return 2;
    case D3DFMT_G16R16F:
        return 4;
    case D3DFMT_A16B16G16R16F:
        return 8;


    case D3DFMT_R32F:
        return 4;
    case D3DFMT_G32R32F:
        return 8;
    case D3DFMT_A32B32G32R32F:
        return 16;

    case D3DFMT_CxV8U8:
        return 2;


    /* Known FourCC formats */
    case D3DFMT_UYVY:
    case D3DFMT_R8G8_B8G8:
    case D3DFMT_YUY2:
    case D3DFMT_G8R8_G8B8:
        return 2;

    case D3DFMT_DXT1:
        return 0xFFFFFFF8;

    case D3DFMT_DXT2:
    case D3DFMT_DXT3:
    case D3DFMT_DXT4:
    case D3DFMT_DXT5:
        return 0xFFFFFFF0;

    case D3DFMT_MULTI2_ARGB8:
        return 8;

    default:
        return 0;
    }
}