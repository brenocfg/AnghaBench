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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void usage(char *progName)
{
  printf("\nUSAGE: %s [options]\n\n", progName);
  printf("Options:\n");
  printf("-yuv = test YUV encoding/decoding support\n");
  printf("-noyuvpad = do not pad each line of each Y, U, and V plane to the nearest\n");
  printf("            4-byte boundary\n");
  printf("-alloc = test automatic buffer allocation\n");
  printf("-bmp = tjLoadImage()/tjSaveImage() unit test\n\n");
  exit(1);
}