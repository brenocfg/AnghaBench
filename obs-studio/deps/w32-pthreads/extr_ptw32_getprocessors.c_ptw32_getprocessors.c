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
typedef  int DWORD_PTR ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetProcessAffinityMask (int /*<<< orphan*/ ,int*,int*) ; 

int
ptw32_getprocessors (int *count)
{
  DWORD_PTR vProcessCPUs;
  DWORD_PTR vSystemCPUs;
  int result = 0;

#if defined(NEED_PROCESS_AFFINITY_MASK)

  *count = 1;

#else

  if (GetProcessAffinityMask (GetCurrentProcess (),
			      &vProcessCPUs, &vSystemCPUs))
    {
      DWORD_PTR bit;
      int CPUs = 0;

      for (bit = 1; bit != 0; bit <<= 1)
	{
	  if (vProcessCPUs & bit)
	    {
	      CPUs++;
	    }
	}
      *count = CPUs;
    }
  else
    {
      result = EAGAIN;
    }

#endif

  return (result);
}