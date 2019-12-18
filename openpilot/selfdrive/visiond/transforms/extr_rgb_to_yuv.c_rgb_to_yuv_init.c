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
typedef  int /*<<< orphan*/  cl_program ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int /*<<< orphan*/  cl_context ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  rgb_to_yuv_krnl; } ;
typedef  TYPE_1__ RGBToYUVState ;

/* Variables and functions */
 int /*<<< orphan*/  CLU_LOAD_FROM_FILE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clCreateKernel (int /*<<< orphan*/ ,char*,int*) ; 
 int clReleaseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int) ; 

void rgb_to_yuv_init(RGBToYUVState* s, cl_context ctx, cl_device_id device_id, int width, int height, int rgb_stride) {
  int err = 0;
  memset(s, 0, sizeof(*s));
  assert(width % 2 == 0);
  assert(height % 2 == 0);
  s->width = width;
  s->height = height;
  char args[1024];
  snprintf(args, sizeof(args),
           "-cl-fast-relaxed-math -cl-denorms-are-zero "
#ifdef CL_DEBUG
           "-DCL_DEBUG "
#endif
           "-DWIDTH=%d -DHEIGHT=%d -DUV_WIDTH=%d -DUV_HEIGHT=%d -DRGB_STRIDE=%d -DRGB_SIZE=%d",
           width, height, width/ 2, height / 2, rgb_stride, width * height);
  cl_program prg = CLU_LOAD_FROM_FILE(ctx, device_id, "transforms/rgb_to_yuv.cl", args);

  s->rgb_to_yuv_krnl = clCreateKernel(prg, "rgb_to_yuv", &err);
  assert(err == 0);
  // done with this
  err = clReleaseProgram(prg);
  assert(err == 0);
}