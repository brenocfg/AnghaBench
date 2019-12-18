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
typedef  int cl_mem ;
typedef  int cl_int ;
typedef  int /*<<< orphan*/  cl_command_queue ;
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  loaduv_krnl; int /*<<< orphan*/  loadys_krnl; } ;
typedef  TYPE_1__ LoadYUVState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int clEnqueueNDRangeKernel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clSetKernelArg (int /*<<< orphan*/ ,int,int,int*) ; 

void loadyuv_queue(LoadYUVState* s, cl_command_queue q,
                   cl_mem y_cl, cl_mem u_cl, cl_mem v_cl,
                   cl_mem out_cl) {
  int err = 0;

  err = clSetKernelArg(s->loadys_krnl, 0, sizeof(cl_mem), &y_cl);
  assert(err == 0);
  err = clSetKernelArg(s->loadys_krnl, 1, sizeof(cl_mem), &out_cl);
  assert(err == 0);

  const size_t loadys_work_size = (s->width*s->height)/8;
  err = clEnqueueNDRangeKernel(q, s->loadys_krnl, 1, NULL,
                               &loadys_work_size, NULL, 0, 0, NULL);
  assert(err == 0);

  const size_t loaduv_work_size = ((s->width/2)*(s->height/2))/8;
  cl_int loaduv_out_off = (s->width*s->height);

  err = clSetKernelArg(s->loaduv_krnl, 0, sizeof(cl_mem), &u_cl);
  assert(err == 0);
  err = clSetKernelArg(s->loaduv_krnl, 1, sizeof(cl_mem), &out_cl);
  assert(err == 0);
  err = clSetKernelArg(s->loaduv_krnl, 2, sizeof(cl_int), &loaduv_out_off);
  assert(err == 0);

  err = clEnqueueNDRangeKernel(q, s->loaduv_krnl, 1, NULL,
                               &loaduv_work_size, NULL, 0, 0, NULL);
  assert(err == 0);

  loaduv_out_off += (s->width/2)*(s->height/2);

  err = clSetKernelArg(s->loaduv_krnl, 0, sizeof(cl_mem), &v_cl);
  assert(err == 0);
  err = clSetKernelArg(s->loaduv_krnl, 1, sizeof(cl_mem), &out_cl);
  assert(err == 0);
  err = clSetKernelArg(s->loaduv_krnl, 2, sizeof(cl_int), &loaduv_out_off);
  assert(err == 0);

  err = clEnqueueNDRangeKernel(q, s->loaduv_krnl, 1, NULL,
                               &loaduv_work_size, NULL, 0, 0, NULL);
  assert(err == 0);
}