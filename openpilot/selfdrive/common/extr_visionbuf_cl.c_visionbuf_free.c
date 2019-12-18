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
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  ctx; int /*<<< orphan*/  buf_cl; scalar_t__ handle; } ;
typedef  TYPE_1__ VisionBuf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int clReleaseMemObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clSVMFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void visionbuf_free(const VisionBuf* buf) {
  if (buf->handle) {
    free(buf->addr);
  } else {
    int err = clReleaseMemObject(buf->buf_cl);
    assert(err == 0);
#if __OPENCL_VERSION__ >= 200
    clSVMFree(buf->ctx, buf->addr);
#else
    free(buf->addr);
#endif
  }
}