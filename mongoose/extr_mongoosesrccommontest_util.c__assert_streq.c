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
 int /*<<< orphan*/  _strfail (char const*,char const*,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

int _assert_streq(const char *actual, const char *expected) {
  if (strcmp(actual, expected) != 0) {
    _strfail(actual, expected, -1);
    return 0;
  }
  return 1;
}