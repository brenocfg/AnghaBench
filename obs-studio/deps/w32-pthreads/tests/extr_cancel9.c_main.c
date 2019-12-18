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
 void* PTHREAD_CANCELED ; 
 int /*<<< orphan*/  PTW32_ALERTABLE_ASYNC_CANCEL ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pthread_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ pthread_win32_test_features_np (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_sleep ; 
 int /*<<< orphan*/  test_udp ; 
 int /*<<< orphan*/  test_wait ; 

int
main ()
{
  pthread_t t;
  void *result;

  if (pthread_win32_test_features_np (PTW32_ALERTABLE_ASYNC_CANCEL))
    {
      printf ("Cancel sleeping thread.\n");
      assert (pthread_create (&t, NULL, test_sleep, NULL) == 0);
      /* Sleep for a while; then cancel */
      Sleep (100);
      assert (pthread_cancel (t) == 0);
      assert (pthread_join (t, &result) == 0);
      assert (result == PTHREAD_CANCELED && "test_sleep" != NULL);

      printf ("Cancel waiting thread.\n");
      assert (pthread_create (&t, NULL, test_wait, NULL) == 0);
      /* Sleep for a while; then cancel. */
      Sleep (100);
      assert (pthread_cancel (t) == 0);
      assert (pthread_join (t, &result) == 0);
      assert (result == PTHREAD_CANCELED && "test_wait");

      printf ("Cancel blocked thread (blocked on network I/O).\n");
      assert (pthread_create (&t, NULL, test_udp, NULL) == 0);
      /* Sleep for a while; then cancel. */
      Sleep (100);
      assert (pthread_cancel (t) == 0);
      assert (pthread_join (t, &result) == 0);
      assert (result == PTHREAD_CANCELED && "test_udp" != NULL);
    }
  else
    {
      printf ("Alertable async cancel not available.\n");
    }

  /*
   * Success.
   */
  return 0;
}