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
typedef  int /*<<< orphan*/  cl_mem ;
typedef  int /*<<< orphan*/  cl_device_id ;
typedef  int /*<<< orphan*/  cl_context ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ VisionBuf ;

/* Variables and functions */
 TYPE_1__ visionbuf_allocate_cl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

cl_mem visionbuf_to_cl(const VisionBuf* buf, cl_device_id device_id, cl_context ctx) {
  // HACK because this platform is just for convenience
  VisionBuf *w_buf = (VisionBuf*)buf;
  cl_mem ret;
  *w_buf = visionbuf_allocate_cl(buf->len, device_id, ctx, &ret);
  return ret;
}