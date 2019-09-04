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
 scalar_t__ isspace (char) ; 

char *trim (char *in)
{
  if (!in)
    return "";

  char *out = 0;
  while (*in)
  {
    if (!out && !isspace (*in))
      out = in;
    ++in;
  }
  if (!out)
    return "";
  while (--in > out && isspace (*in))
    ;
  in[1] = 0;
  return out;
}