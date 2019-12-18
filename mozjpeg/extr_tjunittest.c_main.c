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
 int /*<<< orphan*/  TJSAMP_411 ; 
 int /*<<< orphan*/  TJSAMP_420 ; 
 int /*<<< orphan*/  TJSAMP_422 ; 
 int /*<<< orphan*/  TJSAMP_440 ; 
 int /*<<< orphan*/  TJSAMP_444 ; 
 int /*<<< orphan*/  TJSAMP_GRAY ; 
 int /*<<< orphan*/  _3byteFormats ; 
 int /*<<< orphan*/  _4byteFormats ; 
 int /*<<< orphan*/  _onlyGray ; 
 int /*<<< orphan*/  _onlyRGB ; 
 int alloc ; 
 int bmpTest () ; 
 int /*<<< orphan*/  bufSizeTest () ; 
 int /*<<< orphan*/  doTest (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int doYUV ; 
 int exitStatus ; 
 int pad ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
  int i, num4bf = 5;

#ifdef _WIN32
  srand((unsigned int)time(NULL));
#endif
  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      if (!strcasecmp(argv[i], "-yuv")) doYUV = 1;
      else if (!strcasecmp(argv[i], "-noyuvpad")) pad = 1;
      else if (!strcasecmp(argv[i], "-alloc")) alloc = 1;
      else if (!strcasecmp(argv[i], "-bmp")) return bmpTest();
      else usage(argv[0]);
    }
  }
  if (alloc) printf("Testing automatic buffer allocation\n");
  if (doYUV) num4bf = 4;
  doTest(35, 39, _3byteFormats, 2, TJSAMP_444, "test");
  doTest(39, 41, _4byteFormats, num4bf, TJSAMP_444, "test");
  doTest(41, 35, _3byteFormats, 2, TJSAMP_422, "test");
  doTest(35, 39, _4byteFormats, num4bf, TJSAMP_422, "test");
  doTest(39, 41, _3byteFormats, 2, TJSAMP_420, "test");
  doTest(41, 35, _4byteFormats, num4bf, TJSAMP_420, "test");
  doTest(35, 39, _3byteFormats, 2, TJSAMP_440, "test");
  doTest(39, 41, _4byteFormats, num4bf, TJSAMP_440, "test");
  doTest(41, 35, _3byteFormats, 2, TJSAMP_411, "test");
  doTest(35, 39, _4byteFormats, num4bf, TJSAMP_411, "test");
  doTest(39, 41, _onlyGray, 1, TJSAMP_GRAY, "test");
  doTest(41, 35, _3byteFormats, 2, TJSAMP_GRAY, "test");
  doTest(35, 39, _4byteFormats, 4, TJSAMP_GRAY, "test");
  bufSizeTest();
  if (doYUV) {
    printf("\n--------------------\n\n");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_444, "test_yuv0");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_422, "test_yuv0");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_420, "test_yuv0");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_440, "test_yuv0");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_411, "test_yuv0");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_GRAY, "test_yuv0");
    doTest(48, 48, _onlyGray, 1, TJSAMP_GRAY, "test_yuv0");
  }

  return exitStatus;
}