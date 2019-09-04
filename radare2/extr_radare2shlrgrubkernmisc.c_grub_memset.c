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
typedef  int /*<<< orphan*/  grub_size_t ;

/* Variables and functions */

void *
grub_memset (void *s, int c, grub_size_t n)
{
  unsigned char *p = (unsigned char *) s;

  while (n--)
    *p++ = (unsigned char) c;

  return s;
}