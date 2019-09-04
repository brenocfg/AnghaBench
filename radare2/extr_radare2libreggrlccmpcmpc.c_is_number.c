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
 int /*<<< orphan*/  strchr (char*,char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int is_number(const char* s) {
  size_t i;
  for (i = 0; i < strlen(s); i++) { if (!strchr("0123456789", s[i])) { return 0; } }
  return 1;
}