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
struct mg_str {scalar_t__ len; char* p; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 scalar_t__ MG_MALLOC (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static struct mg_str mg_strdup_common(const struct mg_str s,
                                      int nul_terminate) {
  struct mg_str r = {NULL, 0};
  if (s.len > 0 && s.p != NULL) {
    char *sc = (char *) MG_MALLOC(s.len + (nul_terminate ? 1 : 0));
    if (sc != NULL) {
      memcpy(sc, s.p, s.len);
      if (nul_terminate) sc[s.len] = '\0';
      r.p = sc;
      r.len = s.len;
    }
  }
  return r;
}