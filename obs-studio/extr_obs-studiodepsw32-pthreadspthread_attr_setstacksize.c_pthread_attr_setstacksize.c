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
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int ENOSYS ; 

int
pthread_attr_setstacksize (pthread_attr_t * attr, size_t stacksize)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function specifies the size of the stack on
      *      which threads created with 'attr' will run.
      *
      * PARAMETERS
      *      attr
      *              pointer to an instance of pthread_attr_t
      *
      *      stacksize
      *              stack size, in bytes.
      *
      *
      * DESCRIPTION
      *      This function specifies the size of the stack on
      *      which threads created with 'attr' will run.
      *
      *      NOTES:
      *              1)      Function supported only if this macro is
      *                      defined:
      *
      *                              _POSIX_THREAD_ATTR_STACKSIZE
      *
      *              2)      Find the default first (using
      *                      pthread_attr_getstacksize), then increase
      *                      by multiplying.
      *
      *              3)      Only use if thread needs more than the
      *                      default.
      *
      * RESULTS
      *              0               successfully set stack size,
      *              EINVAL          'attr' is invalid or stacksize too
      *                              small or too big.
      *              ENOSYS          function not supported
      *
      * ------------------------------------------------------
      */
{
#if defined(_POSIX_THREAD_ATTR_STACKSIZE)

#if PTHREAD_STACK_MIN > 0

  /*  Verify that the stack size is within range. */
  if (stacksize < PTHREAD_STACK_MIN)
    {
      return EINVAL;
    }

#endif

  if (ptw32_is_attr (attr) != 0)
    {
      return EINVAL;
    }

  /* Everything is okay. */
  (*attr)->stacksize = stacksize;
  return 0;

#else

  return ENOSYS;

#endif /* _POSIX_THREAD_ATTR_STACKSIZE */

}