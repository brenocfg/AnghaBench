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
struct float_pair {int s; scalar_t__ x; } ;

/* Variables and functions */

__attribute__((used)) static void
div_pair(struct float_pair *q, struct float_pair const *a,
         struct float_pair const *b)
{
  q->s = a->s / b->s;
  q->x = a->x - b->x;
}