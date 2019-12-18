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
 int /*<<< orphan*/  _strfail (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

int _assert_streq_nz(const char *actual, const char *expected) {
  size_t n = strlen(expected);
  if (strncmp(actual, expected, n) != 0) {
    _strfail(actual, expected, n);
    return 0;
  }
  return 1;
}