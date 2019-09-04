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
 int /*<<< orphan*/  GRUB_ERR_OUT_OF_RANGE ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 unsigned long long grub_strtoull (char const*,char**,int) ; 

unsigned long
grub_strtoul (const char *str, char **end, int base)
{
  unsigned long long num;

  num = grub_strtoull (str, end, base);
  if (num > ~0UL)
    {
      grub_error (GRUB_ERR_OUT_OF_RANGE, "overflow is detected");
      return ~0UL;
    }

  return (unsigned long) num;
}