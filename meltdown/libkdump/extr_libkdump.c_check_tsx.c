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
 int /*<<< orphan*/  __cpuid_count (int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int __get_cpuid_max (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_tsx() {
#if !defined(NO_TSX) && !defined(FORCE_TSX)
  if (__get_cpuid_max(0, NULL) >= 7) {
    unsigned a, b, c, d;
    __cpuid_count(7, 0, a, b, c, d);
    return (b & (1 << 11)) ? 1 : 0;
  } else
    return 0;
#elif defined(FORCE_TSX)
  return 1;
#else /* defined (NO_TSX) */
  return 0;
#endif
}