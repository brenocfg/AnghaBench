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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  LPLONG ;

/* Variables and functions */
 int InterlockedExchangeAdd (int /*<<< orphan*/ ,long) ; 
 int NUMTHREADS ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  func ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_getunique_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int* seqmap ; 

int
main()
{
  pthread_t t[NUMTHREADS];
  pthread_attr_t attr;
  int i;

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) == 0);

  for (i = 0; i < NUMTHREADS+2; i++)
    {
      seqmap[i] = 0;
    }

  for (i = 0; i < NUMTHREADS; i++)
    {
      if (NUMTHREADS/2 == i)
        {
          /* Include this main thread, which will be an implicit pthread_t */
          seqmap[(int)pthread_getunique_np(pthread_self())] = 1;
        }
      assert(pthread_create(&t[i], &attr, func, NULL) == 0);
    }

  while (NUMTHREADS > InterlockedExchangeAdd((LPLONG)&done, 0L))
    Sleep(100);

  Sleep(100);

  assert(seqmap[0] == 0);
  for (i = 1; i < NUMTHREADS+2; i++)
    {
      assert(seqmap[i] == 1);
    }

  return 0;
}