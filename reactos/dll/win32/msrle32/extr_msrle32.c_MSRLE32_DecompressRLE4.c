#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* palette_map; } ;
struct TYPE_6__ {scalar_t__ biCompression; int biBitCount; int biWidth; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPCBITMAPINFOHEADER ;
typedef  int* LPBYTE ;
typedef  TYPE_2__ CodecInfo ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ BI_RGB ; 
 int DIBWIDTHBYTES (TYPE_1__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ICERR_ERROR ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static LRESULT MSRLE32_DecompressRLE4(const CodecInfo *pi, LPCBITMAPINFOHEADER lpbi,
				      const BYTE *lpIn, LPBYTE lpOut)
{
  int  bytes_per_pixel;
  int  line_size;
  int  pixel_ptr  = 0;
  int  i;
  BOOL bEndFlag   = FALSE;

  assert(pi != NULL);
  assert(lpbi != NULL && lpbi->biCompression == BI_RGB);
  assert(lpIn != NULL && lpOut != NULL);

  bytes_per_pixel = (lpbi->biBitCount + 1) / 8;
  line_size       = DIBWIDTHBYTES(*lpbi);

  do {
    BYTE code0, code1;

    code0 = *lpIn++;
    code1 = *lpIn++;

    if (code0 == 0) {
      int  extra_byte;

      switch (code1) {
      case  0: /* EOL - end of line  */
	pixel_ptr = 0;
	lpOut += line_size;
	break;
      case  1: /* EOI - end of image */
	bEndFlag = TRUE;
	break;
      case  2: /* skip */
	pixel_ptr += *lpIn++ * bytes_per_pixel;
	lpOut     += *lpIn++ * line_size;
	if (pixel_ptr >= lpbi->biWidth * bytes_per_pixel) {
	  pixel_ptr = 0;
	  lpOut    += line_size;
	}
	break;
      default: /* absolute mode */
	extra_byte = (((code1 + 1) & (~1)) / 2) & 0x01;

	if (pixel_ptr/bytes_per_pixel + code1 > lpbi->biWidth)
	  return ICERR_ERROR;

	code0 = code1;
	for (i = 0; i < code0 / 2; i++) {
	  if (bytes_per_pixel == 1) {
	    code1 = lpIn[i];
	    lpOut[pixel_ptr++] = pi->palette_map[(code1 >> 4)];
	    if (2 * i + 1 <= code0)
	      lpOut[pixel_ptr++] = pi->palette_map[(code1 & 0x0F)];
	  } else if (bytes_per_pixel == 2) {
	    code1 = lpIn[i] >> 4;
	    lpOut[pixel_ptr++] = pi->palette_map[code1 * 2 + 0];
	    lpOut[pixel_ptr++] = pi->palette_map[code1 * 2 + 1];

	    if (2 * i + 1 <= code0) {
	      code1 = lpIn[i] & 0x0F;
	      lpOut[pixel_ptr++] = pi->palette_map[code1 * 2 + 0];
	      lpOut[pixel_ptr++] = pi->palette_map[code1 * 2 + 1];
	    }
	  } else {
	    code1 = lpIn[i] >> 4;
	    lpOut[pixel_ptr + 0] = pi->palette_map[code1 * 4 + 0];
	    lpOut[pixel_ptr + 1] = pi->palette_map[code1 * 4 + 1];
	    lpOut[pixel_ptr + 2] = pi->palette_map[code1 * 4 + 2];
	    pixel_ptr += bytes_per_pixel;

	    if (2 * i + 1 <= code0) {
	      code1 = lpIn[i] & 0x0F;
	      lpOut[pixel_ptr + 0] = pi->palette_map[code1 * 4 + 0];
	      lpOut[pixel_ptr + 1] = pi->palette_map[code1 * 4 + 1];
	      lpOut[pixel_ptr + 2] = pi->palette_map[code1 * 4 + 2];
	      pixel_ptr += bytes_per_pixel;
	    }
	  }
	}
	if (code0 & 0x01) {
	  if (bytes_per_pixel == 1) {
	    code1 = lpIn[i];
	    lpOut[pixel_ptr++] = pi->palette_map[(code1 >> 4)];
	  } else if (bytes_per_pixel == 2) {
	    code1 = lpIn[i] >> 4;
	    lpOut[pixel_ptr++] = pi->palette_map[code1 * 2 + 0];
	    lpOut[pixel_ptr++] = pi->palette_map[code1 * 2 + 1];
	  } else {
	    code1 = lpIn[i] >> 4;
	    lpOut[pixel_ptr + 0] = pi->palette_map[code1 * 4 + 0];
	    lpOut[pixel_ptr + 1] = pi->palette_map[code1 * 4 + 1];
	    lpOut[pixel_ptr + 2] = pi->palette_map[code1 * 4 + 2];
	    pixel_ptr += bytes_per_pixel;
	  }
	  lpIn++;
	}
	lpIn += code0 / 2;

	/* if the RLE code is odd, skip a byte in the stream */
	if (extra_byte)
	  lpIn++;
      };
    } else {
      /* coded mode */
      if (pixel_ptr/bytes_per_pixel + code0 > lpbi->biWidth)
	return ICERR_ERROR;

      if (bytes_per_pixel == 1) {
	BYTE c1 = pi->palette_map[(code1 >> 4)];
	BYTE c2 = pi->palette_map[(code1 & 0x0F)];

	for (i = 0; i < code0; i++) {
	  if ((i & 1) == 0)
	    lpOut[pixel_ptr++] = c1;
	  else
	    lpOut[pixel_ptr++] = c2;
	}
      } else if (bytes_per_pixel == 2) {
	BYTE hi1 = pi->palette_map[(code1 >> 4) * 2 + 0];
	BYTE lo1 = pi->palette_map[(code1 >> 4) * 2 + 1];

	BYTE hi2 = pi->palette_map[(code1 & 0x0F) * 2 + 0];
	BYTE lo2 = pi->palette_map[(code1 & 0x0F) * 2 + 1];

	for (i = 0; i < code0; i++) {
	  if ((i & 1) == 0) {
	    lpOut[pixel_ptr++] = hi1;
	    lpOut[pixel_ptr++] = lo1;
	  } else {
	    lpOut[pixel_ptr++] = hi2;
	    lpOut[pixel_ptr++] = lo2;
	  }
	}
      } else {
	BYTE b1 = pi->palette_map[(code1 >> 4) * 4 + 0];
	BYTE g1 = pi->palette_map[(code1 >> 4) * 4 + 1];
	BYTE r1 = pi->palette_map[(code1 >> 4) * 4 + 2];

	BYTE b2 = pi->palette_map[(code1 & 0x0F) * 4 + 0];
	BYTE g2 = pi->palette_map[(code1 & 0x0F) * 4 + 1];
	BYTE r2 = pi->palette_map[(code1 & 0x0F) * 4 + 2];

	for (i = 0; i < code0; i++) {
	  if ((i & 1) == 0) {
	    lpOut[pixel_ptr + 0] = b1;
	    lpOut[pixel_ptr + 1] = g1;
	    lpOut[pixel_ptr + 2] = r1;
	  } else {
	    lpOut[pixel_ptr + 0] = b2;
	    lpOut[pixel_ptr + 1] = g2;
	    lpOut[pixel_ptr + 2] = r2;
	  }
	  pixel_ptr += bytes_per_pixel;
	}
      }
    }
  } while (! bEndFlag);

  return ICERR_OK;
}