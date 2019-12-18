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
struct mg_str {scalar_t__ len; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 

void mg_strfree(struct mg_str *s) {
  char *sp = (char *) s->p;
  s->p = NULL;
  s->len = 0;
  if (sp != NULL) free(sp);
}