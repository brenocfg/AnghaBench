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
typedef  scalar_t__ vgtod_t ;
typedef  scalar_t__ vgettime_t ;
typedef  void* getcpu_t ;

/* Variables and functions */
 int RTLD_LAZY ; 
 int RTLD_LOCAL ; 
 int RTLD_NOLOAD ; 
 void* dlopen (char*,int) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ vdso_clock_gettime ; 
 void* vdso_getcpu ; 
 scalar_t__ vdso_gettimeofday ; 
 void* vgetcpu ; 
 scalar_t__ vsyscall_getcpu () ; 

__attribute__((used)) static void fill_function_pointers()
{
	void *vdso = dlopen("linux-vdso.so.1",
			    RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	if (!vdso)
		vdso = dlopen("linux-gate.so.1",
			      RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	if (!vdso) {
		printf("[WARN]\tfailed to find vDSO\n");
		return;
	}

	vdso_getcpu = (getcpu_t)dlsym(vdso, "__vdso_getcpu");
	if (!vdso_getcpu)
		printf("Warning: failed to find getcpu in vDSO\n");

	vgetcpu = (getcpu_t) vsyscall_getcpu();

	vdso_clock_gettime = (vgettime_t)dlsym(vdso, "__vdso_clock_gettime");
	if (!vdso_clock_gettime)
		printf("Warning: failed to find clock_gettime in vDSO\n");

	vdso_gettimeofday = (vgtod_t)dlsym(vdso, "__vdso_gettimeofday");
	if (!vdso_gettimeofday)
		printf("Warning: failed to find gettimeofday in vDSO\n");

}