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
 scalar_t__ FOIL (int) ; 
 int PTHREAD_MUTEX_DEFAULT ; 
 int PTHREAD_MUTEX_ERRORCHECK ; 
 scalar_t__ PTHREAD_MUTEX_ERRORCHECK_NP ; 
 scalar_t__ PTHREAD_MUTEX_FAST_NP ; 
 int PTHREAD_MUTEX_NORMAL ; 
 int PTHREAD_MUTEX_RECURSIVE ; 
 scalar_t__ PTHREAD_MUTEX_RECURSIVE_NP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mxAttr ; 
 scalar_t__ pthread_mutexattr_gettype (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ pthread_mutexattr_init (int /*<<< orphan*/ *) ; 

int
main()
{
  int mxType = -1;

  assert(FOIL(PTHREAD_MUTEX_DEFAULT) == PTHREAD_MUTEX_NORMAL);
  assert(FOIL(PTHREAD_MUTEX_DEFAULT) != PTHREAD_MUTEX_ERRORCHECK);
  assert(FOIL(PTHREAD_MUTEX_DEFAULT) != PTHREAD_MUTEX_RECURSIVE);
  assert(FOIL(PTHREAD_MUTEX_RECURSIVE) != PTHREAD_MUTEX_ERRORCHECK);

  assert(FOIL(PTHREAD_MUTEX_NORMAL) == PTHREAD_MUTEX_FAST_NP);
  assert(FOIL(PTHREAD_MUTEX_RECURSIVE) == PTHREAD_MUTEX_RECURSIVE_NP);
  assert(FOIL(PTHREAD_MUTEX_ERRORCHECK) == PTHREAD_MUTEX_ERRORCHECK_NP);

  assert(pthread_mutexattr_init(&mxAttr) == 0);
  assert(pthread_mutexattr_gettype(&mxAttr, &mxType) == 0);
  assert(mxType == PTHREAD_MUTEX_NORMAL);

  return 0;
}