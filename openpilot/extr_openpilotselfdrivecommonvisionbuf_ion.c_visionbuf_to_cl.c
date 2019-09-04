#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  host_cache_policy; int /*<<< orphan*/  allocation_type; } ;
struct TYPE_7__ {scalar_t__ ion_hostptr; int /*<<< orphan*/  ion_filedesc; TYPE_1__ ext_host_ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ cl_mem_ion_host_ptr ;
typedef  int /*<<< orphan*/  cl_mem ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int /*<<< orphan*/  cl_context ;
struct TYPE_8__ {int /*<<< orphan*/  len; scalar_t__ addr; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ VisionBuf ;

/* Variables and functions */
 int CL_MEM_EXT_HOST_PTR_QCOM ; 
 int /*<<< orphan*/  CL_MEM_HOST_UNCACHED_QCOM ; 
 int /*<<< orphan*/  CL_MEM_ION_HOST_PTR_QCOM ; 
 int CL_MEM_USE_HOST_PTR ; 
 uintptr_t DEVICE_PAGE_SIZE_CL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clCreateBuffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*,int*) ; 

cl_mem visionbuf_to_cl(const VisionBuf* buf, cl_device_id device_id, cl_context ctx) {
  int err = 0;

  assert(((uintptr_t)buf->addr % DEVICE_PAGE_SIZE_CL) == 0);

  cl_mem_ion_host_ptr ion_cl = {0};
  ion_cl.ext_host_ptr.allocation_type = CL_MEM_ION_HOST_PTR_QCOM;
  ion_cl.ext_host_ptr.host_cache_policy = CL_MEM_HOST_UNCACHED_QCOM;
  ion_cl.ion_filedesc = buf->fd;
  ion_cl.ion_hostptr = buf->addr;

  cl_mem mem = clCreateBuffer(ctx,
                              CL_MEM_USE_HOST_PTR | CL_MEM_EXT_HOST_PTR_QCOM,
                              buf->len, &ion_cl, &err);
  assert(err == 0);

  return mem;
}