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
struct TYPE_3__ {int /*<<< orphan*/  loaduv_krnl; int /*<<< orphan*/  loadys_krnl; } ;
typedef  TYPE_1__ LoadYUVState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int clReleaseKernel (int /*<<< orphan*/ ) ; 

void loadyuv_destroy(LoadYUVState* s) {
  int err = 0;

  err = clReleaseKernel(s->loadys_krnl);
  assert(err == 0);
  err = clReleaseKernel(s->loaduv_krnl);
  assert(err == 0);
}