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
 int NUM_CV ; 
 int RAND_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** cv ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 void* pthread_timechange_handler_np (int /*<<< orphan*/ *) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
main()
{
  int i, j;

  for (i = 0; i < NUM_CV; i++)
    {
      /* Traverse the list before every init of a CV. */
      assert(pthread_timechange_handler_np(NULL) == (void *) 0);
      assert(pthread_cond_init(&cv[i], NULL) == 0);
    }

  j = NUM_CV;
  (void) srand((unsigned)time(NULL));

  do
    {
      i = (NUM_CV - 1) * rand() / RAND_MAX;
      if (cv[i] != NULL)
        {
          j--;
          assert(pthread_cond_destroy(&cv[i]) == 0);
          /* Traverse the list every time we remove a CV. */
          assert(pthread_timechange_handler_np(NULL) == (void *) 0);
        }
    }
  while (j > 0);

  return 0;
}