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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cl_program ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int /*<<< orphan*/  cl_context ;
struct TYPE_3__ {scalar_t__ index_hash; int /*<<< orphan*/ * bin_data; int /*<<< orphan*/ * bin_end; } ;

/* Variables and functions */
 int ARRAYSIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int clBuildProgram (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clCreateProgramWithBinary (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int*) ; 
 TYPE_1__* clu_index ; 

cl_program cl_program_from_index(cl_context ctx, cl_device_id device_id, uint64_t index_hash) {
  int err;

  int i;
  for (i=0; i<ARRAYSIZE(clu_index); i++) {
    if (clu_index[i].index_hash == index_hash) {
      break;
    }
  }
  if (i >= ARRAYSIZE(clu_index)) {
    assert(false);
  }

  size_t bin_size = clu_index[i].bin_end - clu_index[i].bin_data;
  const uint8_t *bin_data = clu_index[i].bin_data;

  cl_program prg = clCreateProgramWithBinary(ctx, 1, &device_id, &bin_size, (const uint8_t**)&bin_data, NULL, &err);
  assert(err == 0);

  err = clBuildProgram(prg, 1, &device_id, NULL, NULL, NULL);
  assert(err == 0);

  return prg;
}