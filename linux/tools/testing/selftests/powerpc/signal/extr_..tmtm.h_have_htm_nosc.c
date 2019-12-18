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
 int /*<<< orphan*/  PPC_FEATURE2_HTM_NOSC ; 
 int have_hwcap2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static inline bool have_htm_nosc(void)
{
#ifdef PPC_FEATURE2_HTM_NOSC
	return have_hwcap2(PPC_FEATURE2_HTM_NOSC);
#else
	printf("PPC_FEATURE2_HTM_NOSC not defined, can't check AT_HWCAP2\n");
	return false;
#endif
}