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

/* Variables and functions */

void MainThread() {
  int i;

#ifdef _OPENMP
#  pragma omp parallel for
#endif
  for ( i = 0; i < 4; i++ ) {
#ifdef _OPENMP
      int tid = omp_get_thread_num();
#  pragma omp critical
      printf("Main : tid %d\n",tid);
      _thread((void *)tid);
#endif
  }
  return;
}