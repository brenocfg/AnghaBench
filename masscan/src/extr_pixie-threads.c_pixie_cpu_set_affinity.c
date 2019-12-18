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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentThread () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ SetThreadAffinityMask (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UNUSEDPARM (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void
pixie_cpu_set_affinity(unsigned processor)
{
#if defined WIN32
    DWORD_PTR mask;
    DWORD_PTR result;
    if (processor > 0)
        processor--;
    mask = ((size_t)1)<<processor;

    //printf("mask(%u) = 0x%08x\n", processor, mask);
    result = SetThreadAffinityMask(GetCurrentThread(), mask);
    if (result == 0) {
        fprintf(stderr, "set_affinity: returned error win32:%u\n", (unsigned)GetLastError());
    }
#elif defined(__linux__) && defined(__GNUC__)
    int x;
    pthread_t thread = pthread_self();
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    CPU_SET(processor+1, &cpuset);

    x = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (x != 0) {
        fprintf(stderr, "set_affinity: returned error linux:%d\n", errno);
    }
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__)
    /* FIXME: add code here */
    UNUSEDPARM(x);
#endif
}