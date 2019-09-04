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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_stdout ; 
 int printf (char*,...) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ quiet ; 
 int rand () ; 
 int /*<<< orphan*/  stdout ; 
 double waste_time (int) ; 

__attribute__((used)) static int
do_work_unit (int who, int n)
{
  int		i;
  static int	nchars = 0;
  double	f = 0.0;

  if (quiet)
    i = 0;
  else {
    /*
     * get lock on stdout
     */
    assert(pthread_mutex_lock (&mutex_stdout) == 0);

    /*
     * do our job
     */
    i = printf ("%c", "0123456789abcdefghijklmnopqrstuvwxyz"[who]);

    if (!(++nchars % 50))
      printf ("\n");

    fflush (stdout);

    /*
     * release lock on stdout
     */
    assert(pthread_mutex_unlock (&mutex_stdout) == 0);
  }

  n = rand () % 10000;	/* ignore incoming 'n' */
  f = waste_time (n);

  /* This prevents the statement above from being optimised out */
  if (f > 0.0)
    return(n);

  return (n);
}