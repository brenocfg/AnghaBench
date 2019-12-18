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
typedef  int /*<<< orphan*/  cl_mem ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int /*<<< orphan*/  cl_context ;
typedef  int /*<<< orphan*/  VisionBuf ;

/* Variables and functions */
 int /*<<< orphan*/  visionbuf_allocate (size_t) ; 
 int /*<<< orphan*/  visionbuf_to_cl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VisionBuf visionbuf_allocate_cl(size_t len, cl_device_id device_id, cl_context ctx, cl_mem *out_mem) {
  VisionBuf r = visionbuf_allocate(len);
  *out_mem = visionbuf_to_cl(&r, device_id, ctx);
  return r;
}