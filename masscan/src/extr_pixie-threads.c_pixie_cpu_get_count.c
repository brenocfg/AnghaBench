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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ncpu ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int CPU_COUNT (int /*<<< orphan*/ *) ; 
 int CTL_HW ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 size_t GetProcessAffinityMask (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int HW_NCPU ; 
 int /*<<< orphan*/  MPC_GETNUMSPUS ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  _SC_NPROC_ONLN ; 
 int /*<<< orphan*/  getpid () ; 
 int mpctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned
pixie_cpu_get_count(void)
{
#if defined WIN32
    /* WINDOWS - use GetProcessAffinityMask() function */
    size_t x;
#if defined _M_X64
    DWORD_PTR process_mask = 0;
    DWORD_PTR system_mask = 0;
#else
    unsigned long process_mask = 0;
    unsigned long system_mask = 0;
#endif
    unsigned count = 0;
    unsigned i;

    x = GetProcessAffinityMask(GetCurrentProcess(), &process_mask, &system_mask);
    if (x == 0) {
        printf("GetProcessAffinityMask() returned error %u\n", (unsigned)GetLastError());
        return 1;
    }
    for (i=0; i<32; i++) {
        if (system_mask & 1)
            count++;
        system_mask >>= 1;
    }
    if (count == 0)
        return 1;
    else
        return count;
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
    /* BSD - use sysctl() function */
        int x;
        int mib[2];
        size_t ncpu_length;
        int ncpu = 1;

        mib[0] = CTL_HW;
        mib[1] = HW_NCPU;
        ncpu_length = sizeof(ncpu);
        x = sysctl(mib, 2, &ncpu, &ncpu_length, NULL, 0);
        if (x == -1) {
          perror("sysctl(HW_NCPU) failed");
          return 1;
        } else
          return (unsigned)ncpu;
#elif defined linux
    /* http://linux.die.net/man/2/sched_getaffinity */
    {
        pid_t pid;
        cpu_set_t mask;
        int err;

        /* Gegret our process ID */
        pid = getpid();

        /* Get list of available CPUs for our system */
        err = sched_getaffinity(pid, sizeof(mask), &mask);
        if (err) {
            perror("sched_getaffinity");
            return 1;
        } else {
#ifndef CPU_COUNT
            return 1;
#else
            return CPU_COUNT(&mask);
#endif
        }
    }
#elif defined(_SC_NPROCESSORS_ONLN)
    /* Linux, Solaris, Mac OS>=10.4 */
    return sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_SC_NPROC_ONLN)
    /* Irix */
    return sysconf(_SC_NPROC_ONLN);
#elif defined(MPC_GETNUMSPUS)
    return mpctl(MPC_GETNUMSPUS, 0, 0);
#else
#error need to find CPU count
    /* UNKNOWN - Well, we don't know the type of system which means we won't
     * be able to start multiple threads anyway, so just return '1' */
    return 1;
#endif
}