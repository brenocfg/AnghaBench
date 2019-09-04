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
typedef  int /*<<< orphan*/  cl_mem ;
typedef  int /*<<< orphan*/  cl_event ;
typedef  int /*<<< orphan*/  cl_command_queue ;
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  rgb_to_yuv_krnl; } ;
typedef  TYPE_1__ RGBToYUVState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int clEnqueueNDRangeKernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clReleaseEvent (int /*<<< orphan*/ ) ; 
 int clSetKernelArg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clWaitForEvents (int,int /*<<< orphan*/ *) ; 

void rgb_to_yuv_queue(RGBToYUVState* s, cl_command_queue q, cl_mem rgb_cl, cl_mem yuv_cl) {
  int err = 0;
  err = clSetKernelArg(s->rgb_to_yuv_krnl, 0, sizeof(cl_mem), &rgb_cl);
  assert(err == 0);
  err = clSetKernelArg(s->rgb_to_yuv_krnl, 1, sizeof(cl_mem), &yuv_cl);
  assert(err == 0);
  const size_t work_size[2] = {
    (size_t)(s->width + (s->width % 4 == 0 ? 0 : (4 - s->width % 4))) / 4, 
    (size_t)(s->height + (s->height % 4 == 0 ? 0 : (4 - s->height % 4))) / 4
  };
  cl_event event;
  err = clEnqueueNDRangeKernel(q, s->rgb_to_yuv_krnl, 2, NULL, &work_size[0], NULL, 0, 0, &event);
  assert(err == 0);
  clWaitForEvents(1, &event);
  clReleaseEvent(event);
}