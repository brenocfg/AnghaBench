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
struct mg_str {int len; char const* p; } ;

/* Variables and functions */
 int getu16 (char const*) ; 

__attribute__((used)) static const char *scanto(const char *p, struct mg_str *s) {
  s->len = getu16(p);
  s->p = p + 2;
  return s->p + s->len;
}