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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ PTW32_OBJECT_AUTO_INIT ; 
 scalar_t__ ReleaseMutex (scalar_t__) ; 

int
old_mutex_unlock(old_mutex_t *mutex)
{
  int result = 0;
  old_mutex_t mx;

  if (mutex == NULL || *mutex == NULL)
    {
      return EINVAL;
    }

  mx = *mutex;

  if (mx != (old_mutex_t) PTW32_OBJECT_AUTO_INIT)
    {
      if (mx->mutex == 0)
	{
	  LeaveCriticalSection(&mx->cs);
	}
      else
	{
	  result = (ReleaseMutex (mx->mutex) ? 0 : EINVAL);
	}
    }
  else
    {
      result = EINVAL;
    }

  return(result);
}