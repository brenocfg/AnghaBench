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
struct TYPE_3__ {int biWidth; int biBitCount; int biHeight; } ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONG MSRLE32_GetMaxCompressedSize(LPCBITMAPINFOHEADER lpbi)
{
  LONG a, b, size;

  /* pre-condition */
  assert(lpbi != NULL);

  a = lpbi->biWidth / 255;
  b = lpbi->biWidth % 255;
  if (lpbi->biBitCount <= 4) {
    a /= 2;
    b /= 2;
  }

  size = (2 + a * (2 + ((a + 2) & ~2)) + b * (2 + ((b + 2) & ~2)));
  return size * lpbi->biHeight + 2;
}