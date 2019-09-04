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
typedef  TYPE_1__* pthread_rwlockattr_t ;
struct TYPE_3__ {int pshared; } ;

/* Variables and functions */
 int EINVAL ; 

int
pthread_rwlockattr_getpshared (const pthread_rwlockattr_t * attr,
			       int *pshared)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      Determine whether rwlocks created with 'attr' can be
      *      shared between processes.
      *
      * PARAMETERS
      *      attr
      *              pointer to an instance of pthread_rwlockattr_t
      *
      *      pshared
      *              will be set to one of:
      *
      *                      PTHREAD_PROCESS_SHARED
      *                              May be shared if in shared memory
      *
      *                      PTHREAD_PROCESS_PRIVATE
      *                              Cannot be shared.
      *
      *
      * DESCRIPTION
      *      Rwlocks creatd with 'attr' can be shared between
      *      processes if pthread_rwlock_t variable is allocated
      *      in memory shared by these processes.
      *      NOTES:
      *              1)      pshared rwlocks MUST be allocated in shared
      *                      memory.
      *              2)      The following macro is defined if shared rwlocks
      *                      are supported:
      *                              _POSIX_THREAD_PROCESS_SHARED
      *
      * RESULTS
      *              0               successfully retrieved attribute,
      *              EINVAL          'attr' is invalid,
      *
      * ------------------------------------------------------
      */
{
  int result;

  if ((attr != NULL && *attr != NULL) && (pshared != NULL))
    {
      *pshared = (*attr)->pshared;
      result = 0;
    }
  else
    {
      result = EINVAL;
    }

  return (result);

}