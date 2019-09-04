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
typedef  TYPE_1__* pthread_condattr_t ;
struct TYPE_3__ {int pshared; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int PTHREAD_PROCESS_PRIVATE ; 
 int PTHREAD_PROCESS_SHARED ; 

int
pthread_condattr_setpshared (pthread_condattr_t * attr, int pshared)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      Mutexes created with 'attr' can be shared between
      *      processes if pthread_mutex_t variable is allocated
      *      in memory shared by these processes.
      *
      * PARAMETERS
      *      attr
      *              pointer to an instance of pthread_mutexattr_t
      *
      *      pshared
      *              must be one of:
      *
      *                      PTHREAD_PROCESS_SHARED
      *                              May be shared if in shared memory
      *
      *                      PTHREAD_PROCESS_PRIVATE
      *                              Cannot be shared.
      *
      * DESCRIPTION
      *      Mutexes creatd with 'attr' can be shared between
      *      processes if pthread_mutex_t variable is allocated
      *      in memory shared by these processes.
      *
      *      NOTES:
      *              1)      pshared mutexes MUST be allocated in shared
      *                      memory.
      *
      *              2)      The following macro is defined if shared mutexes
      *                      are supported:
      *                              _POSIX_THREAD_PROCESS_SHARED
      *
      * RESULTS
      *              0               successfully set attribute,
      *              EINVAL          'attr' or pshared is invalid,
      *              ENOSYS          PTHREAD_PROCESS_SHARED not supported,
      *
      * ------------------------------------------------------
      */
{
  int result;

  if ((attr != NULL && *attr != NULL)
      && ((pshared == PTHREAD_PROCESS_SHARED)
	  || (pshared == PTHREAD_PROCESS_PRIVATE)))
    {
      if (pshared == PTHREAD_PROCESS_SHARED)
	{

#if !defined( _POSIX_THREAD_PROCESS_SHARED )
	  result = ENOSYS;
	  pshared = PTHREAD_PROCESS_PRIVATE;
#else
	  result = 0;

#endif /* _POSIX_THREAD_PROCESS_SHARED */

	}
      else
	{
	  result = 0;
	}

      (*attr)->pshared = pshared;
    }
  else
    {
      result = EINVAL;
    }

  return result;

}