#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ p; scalar_t__ x; } ;
typedef  TYPE_1__ pthread_t ;

/* Variables and functions */

int
pthread_equal (pthread_t t1, pthread_t t2)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function returns nonzero if t1 and t2 are equal, else
      *      returns zero
      *
      * PARAMETERS
      *      t1,
      *      t2
      *              thread IDs
      *
      *
      * DESCRIPTION
      *      This function returns nonzero if t1 and t2 are equal, else
      *      returns zero.
      *
      * RESULTS
      *              non-zero        if t1 and t2 refer to the same thread,
      *              0               t1 and t2 do not refer to the same thread
      *
      * ------------------------------------------------------
      */
{
  int result;

  /*
   * We also accept NULL == NULL - treating NULL as a thread
   * for this special case, because there is no error that we can return.
   */
  result = ( t1.p == t2.p && t1.x == t2.x );

  return (result);

}