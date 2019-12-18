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
 int /*<<< orphan*/  TJFLAG_BOTTOMUP ; 
 int TJ_NUMPF ; 
 int doBmpTest (char*,int,int,int,int,int /*<<< orphan*/ ) ; 
 char** pixFormatStr ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int bmpTest(void)
{
  int align, width = 35, height = 39, format;

  for (align = 1; align <= 8; align *= 2) {
    for (format = 0; format < TJ_NUMPF; format++) {
      printf("%s Top-Down BMP (row alignment = %d bytes)  ...  ",
             pixFormatStr[format], align);
      if (doBmpTest("bmp", width, align, height, format, 0) == -1)
        return -1;
      printf("OK.\n");

      printf("%s Top-Down PPM (row alignment = %d bytes)  ...  ",
             pixFormatStr[format], align);
      if (doBmpTest("ppm", width, align, height, format,
                    TJFLAG_BOTTOMUP) == -1)
        return -1;
      printf("OK.\n");

      printf("%s Bottom-Up BMP (row alignment = %d bytes)  ...  ",
             pixFormatStr[format], align);
      if (doBmpTest("bmp", width, align, height, format, 0) == -1)
        return -1;
      printf("OK.\n");

      printf("%s Bottom-Up PPM (row alignment = %d bytes)  ...  ",
             pixFormatStr[format], align);
      if (doBmpTest("ppm", width, align, height, format,
                    TJFLAG_BOTTOMUP) == -1)
        return -1;
      printf("OK.\n");
    }
  }

  return 0;
}