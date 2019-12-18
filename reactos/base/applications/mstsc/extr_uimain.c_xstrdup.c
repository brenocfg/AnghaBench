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
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ xmalloc (int) ; 

char *
xstrdup(const char * s)
{
  int len;
  char * p;

  if (s == 0)
  {
    return 0;
  }
  len = strlen(s);
  p = (char *) xmalloc(len + 1);
  strcpy(p, s);
  return p;
}