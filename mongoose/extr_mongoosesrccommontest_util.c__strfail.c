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
 char* _escape (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 size_t strlen (char const*) ; 

void _strfail(const char *a, const char *e, int len) {
  char *ae, *ee;
  if (len < 0) {
    len = strlen(a);
    if (strlen(e) > (size_t) len) len = strlen(e);
  }
  ae = _escape(a, len);
  ee = _escape(e, len);
  printf("Expected: %s\nActual  : %s\n", ee, ae);
  free(ae);
  free(ee);
}