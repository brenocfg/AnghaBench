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
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bankAccount ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  rdfunc ; 
 int /*<<< orphan*/  wrfunc ; 

int
main()
{
  pthread_t wrt1;
  pthread_t wrt2;
  pthread_t rdt;
  void* wr1Result = (void*)0;
  void* wr2Result = (void*)0;
  void* rdResult = (void*)0;

  bankAccount = 0;

  assert(pthread_create(&wrt1, NULL, wrfunc, NULL) == 0);
  Sleep(50);
  assert(pthread_create(&rdt, NULL, rdfunc, NULL) == 0);
  Sleep(50);
  assert(pthread_create(&wrt2, NULL, wrfunc, NULL) == 0);

  assert(pthread_join(wrt1, &wr1Result) == 0);
  assert(pthread_join(rdt, &rdResult) == 0);
  assert(pthread_join(wrt2, &wr2Result) == 0);

  assert((int)(size_t)wr1Result == 10);
  assert((int)(size_t)rdResult == 10);
  assert((int)(size_t)wr2Result == 20);

  return 0;
}