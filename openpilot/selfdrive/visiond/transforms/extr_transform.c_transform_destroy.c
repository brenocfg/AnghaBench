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
struct TYPE_3__ {int /*<<< orphan*/  krnl; int /*<<< orphan*/  m_uv_cl; int /*<<< orphan*/  m_y_cl; } ;
typedef  TYPE_1__ Transform ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int clReleaseKernel (int /*<<< orphan*/ ) ; 
 int clReleaseMemObject (int /*<<< orphan*/ ) ; 

void transform_destroy(Transform* s) {
  int err = 0;

  err = clReleaseMemObject(s->m_y_cl);
  assert(err == 0);
  err = clReleaseMemObject(s->m_uv_cl);
  assert(err == 0);

  err = clReleaseKernel(s->krnl);
  assert(err == 0);
}