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
typedef  int /*<<< orphan*/  cl_program ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int cl_build_status ;

/* Variables and functions */
 int /*<<< orphan*/  CL_PROGRAM_BUILD_LOG ; 
 int /*<<< orphan*/  CL_PROGRAM_BUILD_STATUS ; 
 int /*<<< orphan*/  assert (char*) ; 
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  clGetProgramBuildInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

void cl_print_build_errors(cl_program program, cl_device_id device) {
  cl_build_status status;
  clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_STATUS,
          sizeof(cl_build_status), &status, NULL);

  size_t log_size;
  clGetProgramBuildInfo(program, device,
          CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

  char* log = calloc(log_size+1, 1);
  assert(log);

  clGetProgramBuildInfo(program, device,
          CL_PROGRAM_BUILD_LOG, log_size+1, log, NULL);

  printf("build failed; status=%d, log:\n%s\n",
          status, log);

  free(log);
}