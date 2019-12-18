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
 scalar_t__ isupper (int) ; 
 int tolower (int) ; 

__attribute__((used)) static int
keymatch(char *arg, const char *keyword, int minchars)
/* Case-insensitive matching of (possibly abbreviated) keyword switches. */
/* keyword is the constant keyword (must be lower case already), */
/* minchars is length of minimum legal abbreviation. */
{
  register int ca, ck;
  register int nmatched = 0;

  while ((ca = *arg++) != '\0') {
    if ((ck = *keyword++) == '\0')
      return 0;                 /* arg longer than keyword, no good */
    if (isupper(ca))            /* force arg to lcase (assume ck is already) */
      ca = tolower(ca);
    if (ca != ck)
      return 0;                 /* no good */
    nmatched++;                 /* count matched characters */
  }
  /* reached end of argument; fail if it's too short for unique abbrev */
  if (nmatched < minchars)
    return 0;
  return 1;                     /* A-OK */
}