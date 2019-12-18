#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int biSizeImage; int biHeight; int /*<<< orphan*/  biCompression; } ;
struct TYPE_11__ {int biSize; int biBitCount; int biClrUsed; } ;
typedef  int /*<<< orphan*/  RGBQUAD ;
typedef  scalar_t__ LRESULT ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  TYPE_2__* LPBITMAPINFOHEADER ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CodecInfo ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int DIBWIDTHBYTES (TYPE_2__) ; 
 scalar_t__ DecompressQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ICERR_BADFORMAT ; 
 scalar_t__ ICERR_BADPARAM ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static LRESULT DecompressGetFormat(CodecInfo *pi, LPCBITMAPINFOHEADER lpbiIn,
				   LPBITMAPINFOHEADER lpbiOut)
{
  DWORD size;

  TRACE("(%p,%p,%p)\n",pi,lpbiIn,lpbiOut);

  /* pre-condition */
  assert(pi != NULL);

  if (lpbiIn == NULL)
    return (lpbiOut != NULL ? ICERR_BADPARAM : 0);

  if (DecompressQuery(pi, lpbiIn, NULL) != ICERR_OK)
    return (lpbiOut != NULL ? ICERR_BADFORMAT : 0);

  size = lpbiIn->biSize;

  if (lpbiIn->biBitCount <= 8) {
    int colors;

    if (lpbiIn->biClrUsed == 0)
      colors = 1 << lpbiIn->biBitCount;
    else
      colors = lpbiIn->biClrUsed;

    size += colors * sizeof(RGBQUAD);
  }

  if (lpbiOut != NULL) {
    memcpy(lpbiOut, lpbiIn, size);
    lpbiOut->biCompression  = BI_RGB;
    lpbiOut->biSizeImage    = DIBWIDTHBYTES(*lpbiOut) * lpbiOut->biHeight;

    return ICERR_OK;
  } else
    return size;
}