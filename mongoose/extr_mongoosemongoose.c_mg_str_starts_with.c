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
struct mg_str {scalar_t__ len; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 struct mg_str MG_MK_STR_N (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mg_strcmp (struct mg_str const,struct mg_str) ; 

int mg_str_starts_with(struct mg_str s, struct mg_str prefix) {
  const struct mg_str sp = MG_MK_STR_N(s.p, prefix.len);
  if (s.len < prefix.len) return 0;
  return (mg_strcmp(sp, prefix) == 0);
}