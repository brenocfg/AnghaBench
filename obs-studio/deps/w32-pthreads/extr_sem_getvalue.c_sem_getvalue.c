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
struct TYPE_3__ {long value; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
sem_getvalue (sem_t * sem, int *sval)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function stores the current count value of the
      *      semaphore.
      * RESULTS
      *
      * Return value
      *
      *       0                  sval has been set.
      *      -1                  failed, error in errno
      *
      *  in global errno
      *
      *      EINVAL              'sem' is not a valid semaphore,
      *      ENOSYS              this function is not supported,
      *
      *
      * PARAMETERS
      *
      *      sem                 pointer to an instance of sem_t
      *
      *      sval                pointer to int.
      *
      * DESCRIPTION
      *      This function stores the current count value of the semaphore
      *      pointed to by sem in the int pointed to by sval.
      */
{
  if (sem == NULL || *sem == NULL || sval == NULL)
    {
      errno = EINVAL;
      return -1;
    }
  else
    {
      long value;
      register sem_t s = *sem;
      int result = 0;

      if ((result = pthread_mutex_lock(&s->lock)) == 0)
        {
	  /* See sem_destroy.c
	   */
	  if (*sem == NULL)
	    {
	      (void) pthread_mutex_unlock (&s->lock);
	      errno = EINVAL;
	      return -1;
	    }

          value = s->value;
          (void) pthread_mutex_unlock(&s->lock);
          *sval = value;
        }

      return result;
    }

}