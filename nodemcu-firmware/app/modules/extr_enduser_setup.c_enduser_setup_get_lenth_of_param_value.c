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
 int strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 

__attribute__((used)) static int enduser_setup_get_lenth_of_param_value(const char *str)
{
  char *found = strpbrk (str, "& ");
  if (!found)
  {
    return strlen(str);
  }
  else
  {
    return found - str;
  }
}