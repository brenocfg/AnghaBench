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
typedef  int grub_size_t ;

/* Variables and functions */
 scalar_t__ grub_malloc (int) ; 
 int /*<<< orphan*/  grub_memcpy (char*,char const*,int) ; 
 int grub_strlen (char const*) ; 

char *
grub_strndup (const char *s, grub_size_t n)
{
  grub_size_t len;
  char *p;

  len = grub_strlen (s);
  if (len > n)
    len = n;
  p = (char *) grub_malloc (len + 1);
  if (! p)
    return 0;

  grub_memcpy (p, s, len);
  p[len] = '\0';
  return p;
}