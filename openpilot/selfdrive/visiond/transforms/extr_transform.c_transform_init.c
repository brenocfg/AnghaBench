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
struct TYPE_4__ {void* m_uv_cl; void* m_y_cl; int /*<<< orphan*/  krnl; } ;
typedef  TYPE_1__ Transform ;

/* Variables and functions */
 int /*<<< orphan*/  CLU_LOAD_FROM_FILE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  CL_MEM_READ_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* clCreateBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  clCreateKernel (int /*<<< orphan*/ ,char*,int*) ; 
 int clReleaseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void transform_init(Transform* s, cl_context ctx, cl_device_id device_id) {
  int err = 0;
  memset(s, 0, sizeof(*s));

  cl_program prg = CLU_LOAD_FROM_FILE(ctx, device_id, "transforms/transform.cl", "");

  s->krnl = clCreateKernel(prg, "warpPerspective", &err);
  assert(err == 0);

  // done with this
  err = clReleaseProgram(prg);
  assert(err == 0);

  s->m_y_cl = clCreateBuffer(ctx, CL_MEM_READ_WRITE, 3*3*sizeof(float), NULL, &err);
  assert(err == 0);

  s->m_uv_cl = clCreateBuffer(ctx, CL_MEM_READ_WRITE, 3*3*sizeof(float), NULL, &err);
  assert(err == 0);
}