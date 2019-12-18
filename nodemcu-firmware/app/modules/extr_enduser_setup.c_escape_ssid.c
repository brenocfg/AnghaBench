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

__attribute__((used)) static char *escape_ssid (char *dst, const char *src)
{
  for (int i = 0; i < 32 && src[i]; ++i)
  {
    if (src[i] == '\\' || src[i] == '"')
    {
      *dst++ = '\\';
    }
    *dst++ = src[i];
  }
  return dst;
}