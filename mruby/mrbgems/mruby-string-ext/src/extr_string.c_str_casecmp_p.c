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
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TOUPPER (char const) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static mrb_bool
str_casecmp_p(const char *s1, mrb_int len1, const char *s2, mrb_int len2)
{
  const char *e1, *e2;

  if (len1 != len2) return FALSE;
  e1 = s1 + len1;
  e2 = s2 + len2;
  while (s1 < e1 && s2 < e2) {
    if (*s1 != *s2 && TOUPPER(*s1) != TOUPPER(*s2)) return FALSE;
    ++s1;
    ++s2;
  }
  return TRUE;
}