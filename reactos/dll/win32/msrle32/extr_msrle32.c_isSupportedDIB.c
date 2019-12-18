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
struct TYPE_4__ {int biSize; int biPlanes; scalar_t__ biCompression; int biBitCount; scalar_t__ biClrUsed; scalar_t__ biHeight; int /*<<< orphan*/  biWidth; } ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  unsigned long DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 scalar_t__ BI_BITFIELDS ; 
 scalar_t__ BI_RGB ; 
 unsigned long DIBWIDTHBYTES (TYPE_1__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL  isSupportedDIB(LPCBITMAPINFOHEADER lpbi)
{
  /* pre-conditions */
  assert(lpbi != NULL);

  /* check structure version/planes/compression */
  if (lpbi->biSize < sizeof(BITMAPINFOHEADER) ||
      lpbi->biPlanes != 1)
    return FALSE;
  if (lpbi->biCompression != BI_RGB &&
      lpbi->biCompression != BI_BITFIELDS)
    return FALSE;

  /* check bit-depth */
  if (lpbi->biBitCount != 1 &&
      lpbi->biBitCount != 4 &&
      lpbi->biBitCount != 8 &&
      lpbi->biBitCount != 15 &&
      lpbi->biBitCount != 16 &&
      lpbi->biBitCount != 24 &&
      lpbi->biBitCount != 32)
    return FALSE;

  /* check for size(s) */
  if (!lpbi->biWidth || !lpbi->biHeight)
    return FALSE; /* image with zero size, makes no sense so error ! */
  if (DIBWIDTHBYTES(*lpbi) * (DWORD)lpbi->biHeight >= (1UL << 31) - 1)
    return FALSE; /* image too big ! */

  /* check for nonexistent colortable for hi- and true-color DIB's */
  if (lpbi->biBitCount >= 15 && lpbi->biClrUsed > 0)
    return FALSE;

  return TRUE;
}