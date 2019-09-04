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
 unsigned int HASHSZ ; 

__attribute__((used)) static unsigned int
grub_env_hashval (const char *s)
{
  unsigned int i = 0;

  /* XXX: This can be done much more efficiently.  */
  while (*s)
    i += 5 * *(s++);

  return i % HASHSZ;
}