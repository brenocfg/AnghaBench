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
typedef  scalar_t__ vgettime_t ;
typedef  scalar_t__ time_func_t ;
typedef  scalar_t__ gtod_t ;
typedef  scalar_t__ getcpu_t ;

/* Variables and functions */
 int RTLD_LAZY ; 
 int RTLD_LOCAL ; 
 int RTLD_NOLOAD ; 
 void* dlopen (char*,int) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ vdso_getcpu ; 
 scalar_t__ vdso_gettime ; 
 scalar_t__ vdso_gtod ; 
 scalar_t__ vdso_time ; 

__attribute__((used)) static void init_vdso(void)
{
	void *vdso = dlopen("linux-vdso.so.1", RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	if (!vdso)
		vdso = dlopen("linux-gate.so.1", RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	if (!vdso) {
		printf("[WARN]\tfailed to find vDSO\n");
		return;
	}

	vdso_gtod = (gtod_t)dlsym(vdso, "__vdso_gettimeofday");
	if (!vdso_gtod)
		printf("[WARN]\tfailed to find gettimeofday in vDSO\n");

	vdso_gettime = (vgettime_t)dlsym(vdso, "__vdso_clock_gettime");
	if (!vdso_gettime)
		printf("[WARN]\tfailed to find clock_gettime in vDSO\n");

	vdso_time = (time_func_t)dlsym(vdso, "__vdso_time");
	if (!vdso_time)
		printf("[WARN]\tfailed to find time in vDSO\n");

	vdso_getcpu = (getcpu_t)dlsym(vdso, "__vdso_getcpu");
	if (!vdso_getcpu) {
		/* getcpu() was never wired up in the 32-bit vDSO. */
		printf("[%s]\tfailed to find getcpu in vDSO\n",
		       sizeof(long) == 8 ? "WARN" : "NOTE");
	}
}