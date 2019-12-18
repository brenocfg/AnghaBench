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
struct TYPE_3__ {int /*<<< orphan*/  rgb_to_yuv_krnl; } ;
typedef  TYPE_1__ RGBToYUVState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int clReleaseKernel (int /*<<< orphan*/ ) ; 

void rgb_to_yuv_destroy(RGBToYUVState* s) {
  int err = 0;
  err = clReleaseKernel(s->rgb_to_yuv_krnl);
  assert(err == 0);
}