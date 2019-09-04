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
 int /*<<< orphan*/  PTHREAD_CANCEL_ASYNCHRONOUS ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcanceltype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *
test_sleep (void *arg)
{
  pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

  Sleep (1000);
  return NULL;

}