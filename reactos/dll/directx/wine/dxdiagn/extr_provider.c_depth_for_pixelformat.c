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
#define  D3DFMT_P8 131 
#define  D3DFMT_R5G6B5 130 
#define  D3DFMT_X1R5G5B5 129 
#define  D3DFMT_X8R8G8B8 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static DWORD depth_for_pixelformat(D3DFORMAT format)
{
    switch (format)
    {
    case D3DFMT_P8: return 8;
    case D3DFMT_X1R5G5B5: return 15;
    case D3DFMT_R5G6B5: return 16;
    /* This case will fail to distinguish an original bpp of 24. */
    case D3DFMT_X8R8G8B8: return 32;
    default:
        FIXME("Unknown D3DFORMAT %d, returning 32 bpp\n", format);
        return 32;
    }
}