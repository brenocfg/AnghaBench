#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int Width; int Height; int Stride; scalar_t__ Reserved; TYPE_2__* Scan0; int /*<<< orphan*/  PixelFormat; } ;
struct TYPE_9__ {int biSize; int biWidth; int biPlanes; int biBitCount; int biSizeImage; int /*<<< orphan*/  biCompression; int /*<<< orphan*/  biHeight; } ;
struct TYPE_10__ {int width; int height; struct TYPE_10__* info; struct TYPE_10__* bits; TYPE_1__ bmiHeader; } ;
typedef  TYPE_2__* PDIBITMAP ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  DIBITMAP ;
typedef  TYPE_3__ BitmapData ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 scalar_t__ GdipBitmapLockBits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GdipBitmapUnlockBits (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ GdipCreateBitmapFromFile (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetImageHeight (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GdipGetImageWidth (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ImageLockModeRead ; 
 int ImageLockModeUserInputBuf ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  PixelFormat32bppPARGB ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

PDIBITMAP
DibLoadImage(LPTSTR lpFilename)
{
    PDIBITMAP lpBitmap;
    GpBitmap  *bitmap;
    BitmapData lock;

    if (GdipCreateBitmapFromFile(lpFilename, &bitmap) != Ok)
    {
        return NULL;
    }

    lpBitmap = HeapAlloc(GetProcessHeap(), 0, sizeof(DIBITMAP));
    if (lpBitmap == NULL)
    {
        GdipDisposeImage((GpImage*)bitmap);
        return NULL;
    }

    lpBitmap->info = HeapAlloc(GetProcessHeap(), 0, sizeof(BITMAPINFO));
    if (lpBitmap->info == NULL)
    {
        HeapFree(GetProcessHeap(), 0, lpBitmap);
        GdipDisposeImage((GpImage*)bitmap);
        return NULL;
    }

    if (GdipGetImageWidth((GpImage*)bitmap, &lpBitmap->width) != Ok ||
        GdipGetImageHeight((GpImage*)bitmap, &lpBitmap->height) != Ok)
    {
        HeapFree(GetProcessHeap(), 0, lpBitmap->info);
        HeapFree(GetProcessHeap(), 0, lpBitmap);
        GdipDisposeImage((GpImage*)bitmap);
        return NULL;
    }

    lpBitmap->bits = HeapAlloc(GetProcessHeap(), 0, lpBitmap->width * lpBitmap->height * 4);
    if (!lpBitmap->bits)
    {
        HeapFree(GetProcessHeap(), 0, lpBitmap->info);
        HeapFree(GetProcessHeap(), 0, lpBitmap);
        GdipDisposeImage((GpImage*)bitmap);
        return NULL;
    }

    ZeroMemory(lpBitmap->info, sizeof(BITMAPINFO));
    lpBitmap->info->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    lpBitmap->info->bmiHeader.biWidth       = lpBitmap->width;
    lpBitmap->info->bmiHeader.biHeight      = -(INT)lpBitmap->height;
    lpBitmap->info->bmiHeader.biPlanes      = 1;
    lpBitmap->info->bmiHeader.biBitCount    = 32;
    lpBitmap->info->bmiHeader.biCompression = BI_RGB;
    lpBitmap->info->bmiHeader.biSizeImage   = lpBitmap->width * lpBitmap->height * 4;

    lock.Width = lpBitmap->width;
    lock.Height = lpBitmap->height;
    lock.Stride = lpBitmap->width * 4;
    lock.PixelFormat = PixelFormat32bppPARGB;
    lock.Scan0  = lpBitmap->bits;
    lock.Reserved = 0;

    if (GdipBitmapLockBits(bitmap, NULL, ImageLockModeRead | ImageLockModeUserInputBuf, PixelFormat32bppPARGB, &lock) != Ok)
    {
        HeapFree(GetProcessHeap(), 0, lpBitmap->bits);
        HeapFree(GetProcessHeap(), 0, lpBitmap->info);
        HeapFree(GetProcessHeap(), 0, lpBitmap);
        GdipDisposeImage((GpImage*)bitmap);
        return NULL;
    }

    GdipBitmapUnlockBits(bitmap, &lock);
    GdipDisposeImage((GpImage*)bitmap);

    return lpBitmap;
}