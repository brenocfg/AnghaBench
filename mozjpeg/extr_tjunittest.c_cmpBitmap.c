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

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJPF_CMYK ; 
 int TJPF_GRAY ; 
 int /*<<< orphan*/  cmyk_to_rgb (unsigned char,unsigned char,unsigned char,unsigned char,unsigned char*,unsigned char*,unsigned char*) ; 
 int* tjAlphaOffset ; 
 int* tjBlueOffset ; 
 int* tjGreenOffset ; 
 int* tjPixelSize ; 
 int* tjRedOffset ; 

int cmpBitmap(unsigned char *buf, int width, int pitch, int height, int pf,
              int flags, int gray2rgb)
{
  int roffset = tjRedOffset[pf];
  int goffset = tjGreenOffset[pf];
  int boffset = tjBlueOffset[pf];
  int aoffset = tjAlphaOffset[pf];
  int ps = tjPixelSize[pf];
  int i, j;

  for (j = 0; j < height; j++) {
    int row = (flags & TJFLAG_BOTTOMUP) ? height - j - 1 : j;

    for (i = 0; i < width; i++) {
      unsigned char r = (i * 256 / width) % 256;
      unsigned char g = (j * 256 / height) % 256;
      unsigned char b = (j * 256 / height + i * 256 / width) % 256;

      if (pf == TJPF_GRAY) {
        if (buf[row * pitch + i * ps] != b)
          return 0;
      } else if (pf == TJPF_CMYK) {
        unsigned char rf, gf, bf;

        cmyk_to_rgb(buf[row * pitch + i * ps + 0],
                    buf[row * pitch + i * ps + 1],
                    buf[row * pitch + i * ps + 2],
                    buf[row * pitch + i * ps + 3], &rf, &gf, &bf);
        if (gray2rgb) {
          if (rf != b || gf != b || bf != b)
            return 0;
        } else if (rf != r || gf != g || bf != b) return 0;
      } else {
        if (gray2rgb) {
          if (buf[row * pitch + i * ps + roffset] != b ||
              buf[row * pitch + i * ps + goffset] != b ||
              buf[row * pitch + i * ps + boffset] != b)
            return 0;
        } else if (buf[row * pitch + i * ps + roffset] != r ||
                   buf[row * pitch + i * ps + goffset] != g ||
                   buf[row * pitch + i * ps + boffset] != b)
          return 0;
        if (aoffset >= 0 && buf[row * pitch + i * ps + aoffset] != 0xFF)
          return 0;
      }
    }
  }
  return 1;
}