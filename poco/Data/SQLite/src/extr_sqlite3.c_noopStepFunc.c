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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/ * sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void noopStepFunc(    /*NO_TEST*/
  sqlite3_context *p,        /*NO_TEST*/
  int n,                     /*NO_TEST*/
  sqlite3_value **a          /*NO_TEST*/
){                           /*NO_TEST*/
  UNUSED_PARAMETER(p);       /*NO_TEST*/
  UNUSED_PARAMETER(n);       /*NO_TEST*/
  UNUSED_PARAMETER(a);       /*NO_TEST*/
  assert(0);                 /*NO_TEST*/
}