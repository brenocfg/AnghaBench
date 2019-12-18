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
struct mg_str {char const* p; int len; } ;

/* Variables and functions */

__attribute__((used)) static void parse_uri_component(const char **p, const char *end,
                                const char *seps, struct mg_str *res) {
  const char *q;
  res->p = *p;
  for (; *p < end; (*p)++) {
    for (q = seps; *q != '\0'; q++) {
      if (**p == *q) break;
    }
    if (*q != '\0') break;
  }
  res->len = (*p) - res->p;
  if (*p < end) (*p)++;
}