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
 unsigned int LL ; 
 unsigned int QQ ; 

void gray_code(unsigned long *h) {
  unsigned int i, j = 1, l = 1, term = LL;

  h[0] = 0;

  for (i = 1; i <= QQ; i++) {
    l = (l << 1);
    term = (term >> 1);
    for (; j < l; j++)
      h[j] = h[l - j - 1] ^ term;
  }
}