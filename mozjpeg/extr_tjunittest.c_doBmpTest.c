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
 char* MD5File (char*,char*) ; 
 int PAD (int,int) ; 
 int TJFLAG_BOTTOMUP ; 
 int TJPF_BGR ; 
 int TJPF_CMYK ; 
 int TJPF_GRAY ; 
 int TJPF_RGB ; 
 int TJPF_UNKNOWN ; 
 int TJPF_XBGR ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwmd5 (char*,char*,char*) ; 
 int /*<<< orphan*/  _throwtj () ; 
 int /*<<< orphan*/  _tj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpBitmap (unsigned char*,int,int,int,int,int,int) ; 
 scalar_t__ exitStatus ; 
 int /*<<< orphan*/  initBitmap (unsigned char*,int,int,int,int,int) ; 
 char** pixFormatStr ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ tjAlloc (int) ; 
 int /*<<< orphan*/  tjFree (unsigned char*) ; 
 unsigned char* tjLoadImage (char*,int*,int,int*,int*,int) ; 
 int* tjPixelSize ; 
 int /*<<< orphan*/  tjSaveImage (char*,unsigned char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int doBmpTest(const char *ext, int width, int align, int height, int pf,
              int flags)
{
  char filename[80], *md5sum, md5buf[65];
  int ps = tjPixelSize[pf], pitch = PAD(width * ps, align), loadWidth = 0,
    loadHeight = 0, retval = 0, pixelFormat = pf;
  unsigned char *buf = NULL;
  char *md5ref;

  if (pf == TJPF_GRAY) {
    md5ref = !strcasecmp(ext, "ppm") ? "112c682e82ce5de1cca089e20d60000b" :
                                       "51976530acf75f02beddf5d21149101d";
  } else {
    md5ref = !strcasecmp(ext, "ppm") ? "c0c9f772b464d1896326883a5c79c545" :
                                       "6d659071b9bfcdee2def22cb58ddadca";
  }

  if ((buf = (unsigned char *)tjAlloc(pitch * height)) == NULL)
    _throw("Could not allocate memory");
  initBitmap(buf, width, pitch, height, pf, flags);

  snprintf(filename, 80, "test_bmp_%s_%d_%s.%s", pixFormatStr[pf], align,
           (flags & TJFLAG_BOTTOMUP) ? "bu" : "td", ext);
  _tj(tjSaveImage(filename, buf, width, pitch, height, pf, flags));
  md5sum = MD5File(filename, md5buf);
  if (strcasecmp(md5sum, md5ref))
    _throwmd5(filename, md5sum, md5ref);

  tjFree(buf);  buf = NULL;
  if ((buf = tjLoadImage(filename, &loadWidth, align, &loadHeight, &pf,
                         flags)) == NULL)
    _throwtj();
  if (width != loadWidth || height != loadHeight) {
    printf("\n   Image dimensions of %s are bogus\n", filename);
    retval = -1;  goto bailout;
  }
  if (!cmpBitmap(buf, width, pitch, height, pf, flags, 0)) {
    printf("\n   Pixel data in %s is bogus\n", filename);
    retval = -1;  goto bailout;
  }
  if (pf == TJPF_GRAY) {
    tjFree(buf);  buf = NULL;
    pf = TJPF_XBGR;
    if ((buf = tjLoadImage(filename, &loadWidth, align, &loadHeight, &pf,
                           flags)) == NULL)
      _throwtj();
    pitch = PAD(width * tjPixelSize[pf], align);
    if (!cmpBitmap(buf, width, pitch, height, pf, flags, 1)) {
      printf("\n   Converting %s to RGB failed\n", filename);
      retval = -1;  goto bailout;
    }

    tjFree(buf);  buf = NULL;
    pf = TJPF_CMYK;
    if ((buf = tjLoadImage(filename, &loadWidth, align, &loadHeight, &pf,
                           flags)) == NULL)
      _throwtj();
    pitch = PAD(width * tjPixelSize[pf], align);
    if (!cmpBitmap(buf, width, pitch, height, pf, flags, 1)) {
      printf("\n   Converting %s to CMYK failed\n", filename);
      retval = -1;  goto bailout;
    }
  }
  /* Verify that tjLoadImage() returns the proper "preferred" pixel format for
     the file type. */
  tjFree(buf);  buf = NULL;
  pf = pixelFormat;
  pixelFormat = TJPF_UNKNOWN;
  if ((buf = tjLoadImage(filename, &loadWidth, align, &loadHeight,
                         &pixelFormat, flags)) == NULL)
    _throwtj();
  if ((pf == TJPF_GRAY && pixelFormat != TJPF_GRAY) ||
      (pf != TJPF_GRAY && !strcasecmp(ext, "bmp") &&
       pixelFormat != TJPF_BGR) ||
      (pf != TJPF_GRAY && !strcasecmp(ext, "ppm") &&
       pixelFormat != TJPF_RGB)) {
    printf("\n   tjLoadImage() returned unexpected pixel format: %s\n",
           pixFormatStr[pixelFormat]);
    retval = -1;
  }
  unlink(filename);

bailout:
  if (buf) tjFree(buf);
  if (exitStatus < 0) return exitStatus;
  return retval;
}