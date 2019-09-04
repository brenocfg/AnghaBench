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
typedef  TYPE_1__* old_mutex_t ;
struct TYPE_3__ {scalar_t__ mutex; int /*<<< orphan*/  cs; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PTW32_OBJECT_AUTO_INIT ; 
 scalar_t__ TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ptw32_try_enter_critical_section (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

int
old_mutex_trylock(old_mutex_t *mutex)
{
  int result = 0;
  old_mutex_t mx;

  if (mutex == NULL || *mutex == NULL)
    {
      return EINVAL;
    }

  if (*mutex == (old_mutex_t) PTW32_OBJECT_AUTO_INIT)
    {
      /*
       * Don't use initialisers when benchtesting.
       */
      result = EINVAL;
    }

  mx = *mutex;

  if (result == 0)
    {
      if (mx->mutex == 0)
	{
	  if (ptw32_try_enter_critical_section == NULL)
          {
            result = 0;
          }
        else if ((*ptw32_try_enter_critical_section)(&mx->cs) != TRUE)
	    {
	      result = EBUSY;
	    }
	}
      else
	{
	  DWORD status;

	  status = WaitForSingleObject (mx->mutex, 0);

	  if (status != WAIT_OBJECT_0)
	    {
	      result = ((status == WAIT_TIMEOUT)
			? EBUSY
			: EINVAL);
	    }
	}
    }

  return(result);
}