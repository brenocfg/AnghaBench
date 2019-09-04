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
struct mg_str {scalar_t__ len; scalar_t__* p; } ;

/* Variables and functions */
 scalar_t__ isspace (int) ; 

struct mg_str mg_strstrip(struct mg_str s) {
  while (s.len > 0 && isspace((int) *s.p)) {
    s.p++;
    s.len--;
  }
  while (s.len > 0 && isspace((int) *(s.p + s.len - 1))) {
    s.len--;
  }
  return s;
}