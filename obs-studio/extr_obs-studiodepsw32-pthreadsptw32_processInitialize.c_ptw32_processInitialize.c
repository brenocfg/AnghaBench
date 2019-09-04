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

/* Variables and functions */
 int PTW32_TRUE ; 
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_cleanupKey ; 
 int ptw32_processInitialized ; 
 int /*<<< orphan*/  ptw32_processTerminate () ; 
 int /*<<< orphan*/  ptw32_selfThreadKey ; 

int
ptw32_processInitialize (void)
     /*
      * ------------------------------------------------------
      * DOCPRIVATE
      *      This function performs process wide initialization for
      *      the pthread library.
      *
      * PARAMETERS
      *      N/A
      *
      * DESCRIPTION
      *      This function performs process wide initialization for
      *      the pthread library.
      *      If successful, this routine sets the global variable
      *      ptw32_processInitialized to TRUE.
      *
      * RESULTS
      *              TRUE    if successful,
      *              FALSE   otherwise
      *
      * ------------------------------------------------------
      */
{
  if (ptw32_processInitialized)
    {
      /* 
       * Ignore if already initialized. this is useful for 
       * programs that uses a non-dll pthread
       * library. Such programs must call ptw32_processInitialize() explicitly,
       * since this initialization routine is automatically called only when
       * the dll is loaded.
       */
      return PTW32_TRUE;
    }

  ptw32_processInitialized = PTW32_TRUE;

  /*
   * Initialize Keys
   */
  if ((pthread_key_create (&ptw32_selfThreadKey, NULL) != 0) ||
      (pthread_key_create (&ptw32_cleanupKey, NULL) != 0))
    {

      ptw32_processTerminate ();
    }

  return (ptw32_processInitialized);

}