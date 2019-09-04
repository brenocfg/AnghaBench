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

/* Variables and functions */
 int NUM_CV ; 
 int NUM_LOOPS ; 
 int RAND_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** cv ; 
 scalar_t__ pthread_cond_destroy (int /*<<< orphan*/ **) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_timechange_handler_np ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
main()
{
  int i, j, k;
  void* result = (void*)-1;
  pthread_t t;

  for (k = 0; k < NUM_LOOPS; k++)
    {
      for (i = 0; i < NUM_CV; i++)
        {
          assert(pthread_cond_init(&cv[i], NULL) == 0);
        }

      j = NUM_CV;
      (void) srand((unsigned)time(NULL));

      /* Traverse the list asynchronously. */
      assert(pthread_create(&t, NULL, pthread_timechange_handler_np, NULL) == 0);

      do
        {
          i = (NUM_CV - 1) * rand() / RAND_MAX;
          if (cv[i] != NULL)
            {
              j--;
              assert(pthread_cond_destroy(&cv[i]) == 0);
            }
        }
      while (j > 0);

      assert(pthread_join(t, &result) == 0);
      assert ((int)(size_t)result == 0);
    }

  return 0;
}