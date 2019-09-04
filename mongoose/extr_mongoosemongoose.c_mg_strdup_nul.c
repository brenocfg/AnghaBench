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
struct mg_str {int dummy; } ;

/* Variables and functions */
 struct mg_str mg_strdup_common (struct mg_str const,int) ; 

struct mg_str mg_strdup_nul(const struct mg_str s) {
  return mg_strdup_common(s, 1 /* NUL-terminate */);
}