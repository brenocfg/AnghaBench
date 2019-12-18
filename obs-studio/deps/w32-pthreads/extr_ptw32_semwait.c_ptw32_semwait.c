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
typedef  TYPE_1__* sem_t ;
struct TYPE_3__ {int value; scalar_t__ leftToUnblock; int /*<<< orphan*/  lock; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 void* EINVAL ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
ptw32_semwait (sem_t * sem)
     /*
      * ------------------------------------------------------
      * DESCRIPTION
      *      This function waits on a POSIX semaphore. If the
      *      semaphore value is greater than zero, it decreases
      *      its value by one. If the semaphore value is zero, then
      *      the calling thread (or process) is blocked until it can
      *      successfully decrease the value.
      *
      *      Unlike sem_wait(), this routine is non-cancelable.
      *
      * RESULTS
      *              0               successfully decreased semaphore,
      *              -1              failed, error in errno.
      * ERRNO
      *              EINVAL          'sem' is not a valid semaphore,
      *              ENOSYS          semaphores are not supported,
      *              EINTR           the function was interrupted by a signal,
      *              EDEADLK         a deadlock condition was detected.
      *
      * ------------------------------------------------------
      */
{
  int result = 0;
  sem_t s = *sem;

  if (s == NULL)
    {
      result = EINVAL;
    }
  else
    {
      if ((result = pthread_mutex_lock (&s->lock)) == 0)
        {
          int v;

	  /* See sem_destroy.c
	   */
	  if (*sem == NULL)
	    {
	      (void) pthread_mutex_unlock (&s->lock);
	      errno = EINVAL;
	      return -1;
	    }

          v = --s->value;
          (void) pthread_mutex_unlock (&s->lock);

          if (v < 0)
            {
              /* Must wait */
              if (WaitForSingleObject (s->sem, INFINITE) == WAIT_OBJECT_0)
		{
#if defined(NEED_SEM)
		  if (pthread_mutex_lock (&s->lock) == 0)
		    {
        	      if (*sem == NULL)
        	        {
        	          (void) pthread_mutex_unlock (&s->lock);
        	          errno = EINVAL;
        	          return -1;
        	        }

		      if (s->leftToUnblock > 0)
			{
			  --s->leftToUnblock;
			  SetEvent(s->sem);
			}
		      (void) pthread_mutex_unlock (&s->lock);
		    }
#endif
		  return 0;
		}
            }
          else
	    {
	      return 0;
	    }
        }
    }

  if (result != 0)
    {
      errno = result;
      return -1;
    }

  return 0;

}