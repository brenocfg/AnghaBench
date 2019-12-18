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
struct TYPE_3__ {unsigned int x; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ pthread_t ;
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
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
main()
{
  pthread_t t[NUMTHREADS];
  pthread_attr_t attr;
  int i;
  unsigned int notUnique = 0,
	       totalHandles = 0,
	       reuseMax = 0,
	       reuseMin = NUMTHREADS;

  assert(pthread_attr_init(&attr) == 0);
  assert(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) == 0);

  for (i = 0; i < NUMTHREADS; i++)
    {
      while(pthread_create(&t[i], &attr, func, NULL) != 0)
        Sleep(1);
    }

  while (NUMTHREADS > InterlockedExchangeAdd((LPLONG)&done, 0L))
    Sleep(100);

  Sleep(100);

  /*
   * Analyse reuse by computing min and max number of times pthread_create()
   * returned the same pthread_t value.
   */
  for (i = 0; i < NUMTHREADS; i++)
    {
      if (t[i].p != NULL)
        {
          unsigned int j, thisMax;

          thisMax = t[i].x;

          for (j = i+1; j < NUMTHREADS; j++)
            if (t[i].p == t[j].p)
              {
		if (t[i].x == t[j].x)
		  notUnique++;
                if (thisMax < t[j].x)
                  thisMax = t[j].x;
                t[j].p = NULL;
              }

          if (reuseMin > thisMax)
            reuseMin = thisMax;

          if (reuseMax < thisMax)
            reuseMax = thisMax;
        }
    }

  for (i = 0; i < NUMTHREADS; i++)
    if (t[i].p != NULL)
      totalHandles++;

  /*
   * pthread_t reuse counts start at 0, so we need to add 1
   * to the max and min values derived above.
   */
  printf("For %d total threads:\n", NUMTHREADS);
  printf("Non-unique IDs = %d\n", notUnique);
  printf("Reuse maximum  = %d\n", reuseMax + 1);
  printf("Reuse minimum  = %d\n", reuseMin + 1);
  printf("Total handles  = %d\n", totalHandles);

  return 0;
}