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
 scalar_t__ ISSPACE (char const) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
check_keyword(const char *buf, const char *word)
{
  const char *p = buf;
  size_t len = strlen(word);

  /* skip preceding spaces */
  while (*p && ISSPACE(*p)) {
    p++;
  }
  /* check keyword */
  if (strncmp(p, word, len) != 0) {
    return 0;
  }
  p += len;
  /* skip trailing spaces */
  while (*p) {
    if (!ISSPACE(*p)) return 0;
    p++;
  }
  return 1;
}