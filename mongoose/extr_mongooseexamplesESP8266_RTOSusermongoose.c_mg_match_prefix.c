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
struct mg_str {char const* member_0; size_t member_1; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 size_t mg_match_prefix_n (struct mg_str const,struct mg_str) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

size_t mg_match_prefix(const char *pattern, int pattern_len, const char *str) {
  const struct mg_str pstr = {pattern, (size_t) pattern_len};
  struct mg_str s = {str, 0};
  if (str != NULL) s.len = strlen(str);
  return mg_match_prefix_n(pstr, s);
}