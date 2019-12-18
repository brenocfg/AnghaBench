#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
struct nk_image {int w; int h; int* region; TYPE_2__ handle; } ;
struct TYPE_6__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_8__ {TYPE_1__ bmiHeader; int /*<<< orphan*/  member_0; } ;
typedef  unsigned char* LPBYTE ;
typedef  int const INT ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  SetDIBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,unsigned char*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nk_create_image(struct nk_image * image, const char * frame_buffer, const int width, const int height)
{
    if (image && frame_buffer && (width > 0) && (height > 0))
    {
        image->w = width;
        image->h = height;
        image->region[0] = 0;
        image->region[1] = 0;
        image->region[2] = width;
        image->region[3] = height;
        
        INT row = ((width * 3 + 3) & ~3);
        BITMAPINFO bi = { 0 };
        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bi.bmiHeader.biWidth = width;
        bi.bmiHeader.biHeight = height;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 24;
        bi.bmiHeader.biCompression = BI_RGB;
        bi.bmiHeader.biSizeImage = row * height;
        
        LPBYTE lpBuf, pb = NULL;
        HBITMAP hbm = CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, (void**)&lpBuf, NULL, 0);
        
        pb = lpBuf + row * height;
        unsigned char * src = (unsigned char *)frame_buffer;
        for (int v = 0; v<height; v++)
        {
            pb -= row;
            for (int i = 0; i < row; i += 3)
            {
                pb[i + 0] = src[0];
                pb[i + 1] = src[1];
                pb[i + 2] = src[2];
                src += 3;
            }
        }        
        SetDIBits(NULL, hbm, 0, height, lpBuf, &bi, DIB_RGB_COLORS);
        image->handle.ptr = hbm;
    }
}