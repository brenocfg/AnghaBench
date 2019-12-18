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
typedef  TYPE_1__* pthread_mutexattr_t ;
struct TYPE_3__ {int robustness; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PTHREAD_MUTEX_ROBUST 129 
#define  PTHREAD_MUTEX_STALLED 128 

int
pthread_mutexattr_setrobust (pthread_mutexattr_t * attr, int robust)
     /*
      * ------------------------------------------------------
      *
      * DOCPUBLIC
      * The pthread_mutexattr_setrobust() and
      * pthread_mutexattr_getrobust() functions  respectively set and
      * get the mutex robust  attribute. This attribute is set in  the
      * robust parameter to these functions.
      *
      * PARAMETERS
      *      attr
      *              pointer to an instance of pthread_mutexattr_t
      *
      *     robust 
      *              must be one of:
      *
      *                      PTHREAD_MUTEX_STALLED
      *
      *                      PTHREAD_MUTEX_ROBUST
      *
      * DESCRIPTION
      * The pthread_mutexattr_setrobust() and
      * pthread_mutexattr_getrobust() functions  respectively set and
      * get the mutex robust  attribute. This attribute is set in  the
      * robust  parameter to these functions. The default value of the
      * robust  attribute is  PTHREAD_MUTEX_STALLED.
      * 
      * The robustness of mutex is contained in the robustness attribute
      * of the mutex attributes. Valid mutex robustness values are:
      *
      * PTHREAD_MUTEX_STALLED
      * No special actions are taken if the owner of the mutex is
      * terminated while holding the mutex lock. This can lead to
      * deadlocks if no other thread can unlock the mutex.
      * This is the default value.
      * 
      * PTHREAD_MUTEX_ROBUST
      * If the process containing the owning thread of a robust mutex
      * terminates while holding the mutex lock, the next thread that
      * acquires the mutex shall be notified about the termination by
      * the return value [EOWNERDEAD] from the locking function. If the
      * owning thread of a robust mutex terminates while holding the mutex
      * lock, the next thread that acquires the mutex may be notified
      * about the termination by the return value [EOWNERDEAD]. The
      * notified thread can then attempt to mark the state protected by
      * the mutex as consistent again by a call to
      * pthread_mutex_consistent(). After a subsequent successful call to
      * pthread_mutex_unlock(), the mutex lock shall be released and can
      * be used normally by other threads. If the mutex is unlocked without
      * a call to pthread_mutex_consistent(), it shall be in a permanently
      * unusable state and all attempts to lock the mutex shall fail with
      * the error [ENOTRECOVERABLE]. The only permissible operation on such
      * a mutex is pthread_mutex_destroy().
      *
      * RESULTS
      *              0               successfully set attribute,
      *              EINVAL          'attr' or 'robust' is invalid,
      *
      * ------------------------------------------------------
      */
{
  int result = EINVAL;

  if ((attr != NULL && *attr != NULL))
    {
      switch (robust)
        {
          case PTHREAD_MUTEX_STALLED:
          case PTHREAD_MUTEX_ROBUST:
	    (*attr)->robustness = robust;
            result = 0;
            break;
        }
    }

  return (result);
}