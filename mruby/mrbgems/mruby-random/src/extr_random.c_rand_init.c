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
struct TYPE_3__ {int* seed; } ;
typedef  TYPE_1__ rand_state ;

/* Variables and functions */

__attribute__((used)) static void
rand_init(rand_state *t)
{
  t->seed[0] = 123456789;
  t->seed[1] = 362436069;
  t->seed[2] = 521288629;
#ifndef XORSHIFT96
  t->seed[3] = 88675123;
#endif
}