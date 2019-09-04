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
struct TYPE_3__ {int id; int work; int stat; int /*<<< orphan*/  mutex_ended; int /*<<< orphan*/  mutex_end; int /*<<< orphan*/  mutex_started; int /*<<< orphan*/  mutex_start; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ TC ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dosync () ; 
 int /*<<< orphan*/  dowork () ; 
 int /*<<< orphan*/  mutex_stdout ; 
 int /*<<< orphan*/  mutex_todo ; 
 int nthreads ; 
 scalar_t__ print_server ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* tcs ; 
 int todo ; 

int
main (int argc, char *argv[])
{
  int		i;

  assert(NULL != (tcs = (TC *) calloc (nthreads, sizeof (*tcs))));

  /* 
   * Launch threads
   */
  for (i = 0; i < nthreads; ++i)
    {
      tcs[i].id = i;

      assert(pthread_mutex_init (&tcs[i].mutex_start, NULL) == 0);
      assert(pthread_mutex_init (&tcs[i].mutex_started, NULL) == 0);
      assert(pthread_mutex_init (&tcs[i].mutex_end, NULL) == 0);
      assert(pthread_mutex_init (&tcs[i].mutex_ended, NULL) == 0);

      tcs[i].work = 0;  

      assert(pthread_mutex_lock (&tcs[i].mutex_start) == 0);
      assert((tcs[i].stat = 
	      pthread_create (&tcs[i].thread,
			      NULL,
                  (void *(*)(void *))print_server,
                (void *) &tcs[i])
	      ) == 0);

      /* 
       * Wait for thread initialisation
       */
      {
	int trylock = 0;

	while (trylock == 0)
	  {
	    trylock = pthread_mutex_trylock(&tcs[i].mutex_started);
	    assert(trylock == 0 || trylock == EBUSY);

	    if (trylock == 0)
	      {
		assert(pthread_mutex_unlock (&tcs[i].mutex_started) == 0);
	      }
	  }
      }
    }

  dowork ();

  /*
   * Terminate threads
   */
  todo = -2;	/* please terminate */
  dosync();

  for (i = 0; i < nthreads; ++i)
    {
      if (0 == tcs[i].stat)
	assert(pthread_join (tcs[i].thread, NULL) == 0);
    }

  /* 
   * destroy locks
   */
  assert(pthread_mutex_destroy (&mutex_stdout) == 0);
  assert(pthread_mutex_destroy (&mutex_todo) == 0);

  /*
   * Cleanup
   */
  printf ("\n");

  /*
   * Show results
   */
  for (i = 0; i < nthreads; ++i)
    {
      printf ("%2d ", i);
      if (0 == tcs[i].stat)
	printf ("%10ld\n", tcs[i].work);
      else
	printf ("failed %d\n", tcs[i].stat);

      assert(pthread_mutex_unlock(&tcs[i].mutex_start) == 0);

      assert(pthread_mutex_destroy (&tcs[i].mutex_start) == 0);
      assert(pthread_mutex_destroy (&tcs[i].mutex_started) == 0);
      assert(pthread_mutex_destroy (&tcs[i].mutex_end) == 0);
      assert(pthread_mutex_destroy (&tcs[i].mutex_ended) == 0);
    }

  die (0);

  return (0);
}