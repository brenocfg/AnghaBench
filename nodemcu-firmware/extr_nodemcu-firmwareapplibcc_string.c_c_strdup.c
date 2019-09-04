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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* os_malloc (int) ; 
 int os_strlen (char const*) ; 

char *c_strdup(const char *c) {
  int len = os_strlen(c) + 1;
  char *ret = os_malloc(len);
  if (ret) {
    memcpy(ret, c, len);
  }
  return ret;
}