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
typedef  scalar_t__ DIGIT_T ;

/* Variables and functions */

__attribute__((used)) static void
mpSetZero(DIGIT_T* a, unsigned int ndigits)
{ /* Sets a = 0 */
  unsigned int i;

  for (i = 0; i < ndigits; i++)
  {
    a[i] = 0;
  }
}