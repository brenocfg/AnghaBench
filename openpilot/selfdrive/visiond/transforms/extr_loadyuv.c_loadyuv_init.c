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
struct TYPE_4__ {int width; int height; void* loaduv_krnl; void* loadys_krnl; } ;
typedef  TYPE_1__ LoadYUVState ;

/* Variables and functions */
 int /*<<< orphan*/  CLU_LOAD_FROM_FILE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* clCreateKernel (int /*<<< orphan*/ ,char*,int*) ; 
 int clReleaseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

void loadyuv_init(LoadYUVState* s, cl_context ctx, cl_device_id device_id, int width, int height) {
  int err = 0;
  memset(s, 0, sizeof(*s));

  s->width = width;
  s->height = height;

  char args[1024];
  snprintf(args, sizeof(args),
           "-cl-fast-relaxed-math -cl-denorms-are-zero "
           "-DTRANSFORMED_WIDTH=%d -DTRANSFORMED_HEIGHT=%d",
           width, height);
  cl_program prg = CLU_LOAD_FROM_FILE(ctx, device_id, "transforms/loadyuv.cl", args);

  s->loadys_krnl = clCreateKernel(prg, "loadys", &err);
  assert(err == 0);
  s->loaduv_krnl = clCreateKernel(prg, "loaduv", &err);
  assert(err == 0);

  // done with this
  err = clReleaseProgram(prg);
  assert(err == 0);
}