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
struct TYPE_3__ {int biSize; int biPlanes; scalar_t__ biCompression; int biBitCount; int biWidth; } ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;

/* Variables and functions */
 scalar_t__ BI_RLE4 ; 
 scalar_t__ BI_RLE8 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL isSupportedMRLE(LPCBITMAPINFOHEADER lpbi)
{
  /* pre-conditions */
  assert(lpbi != NULL);

  if (lpbi->biSize < sizeof(BITMAPINFOHEADER) ||
      lpbi->biPlanes != 1)
    return FALSE;

  if (lpbi->biCompression == BI_RLE4) {
    if (lpbi->biBitCount != 4 ||
	(lpbi->biWidth % 2) != 0)
      return FALSE;
  } else if (lpbi->biCompression == BI_RLE8) {
    if (lpbi->biBitCount != 8)
      return FALSE;
  } else
    return FALSE;

  return TRUE;
}