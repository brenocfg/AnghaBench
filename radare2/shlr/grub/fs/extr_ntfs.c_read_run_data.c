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
typedef  unsigned char grub_disk_addr_t ;

/* Variables and functions */

__attribute__((used)) static char *
read_run_data (char *run, int nn, grub_disk_addr_t * val, int sig)
{
  grub_disk_addr_t r, v;

  r = 0;
  v = 1;

  while (nn--)
    {
      r += v * (*(unsigned char *) (run++));
      v <<= 8;
    }

  if ((sig) && (r & (v >> 1)))
    r -= v;

  *val = r;
  return run;
}