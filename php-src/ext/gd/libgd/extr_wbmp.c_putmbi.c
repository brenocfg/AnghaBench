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

void
putmbi (int i, void (*putout) (int c, void *out), void *out)
{
  int cnt, l, accu;

  /* Get number of septets */
  cnt = 0;
  accu = 0;
  while (accu != i)
    accu += i & 0x7f << 7 * cnt++;

  /* Produce the multibyte output */
  for (l = cnt - 1; l > 0; l--)
    putout (0x80 | (i & 0x7f << 7 * l) >> 7 * l, out);

  putout (i & 0x7f, out);

}