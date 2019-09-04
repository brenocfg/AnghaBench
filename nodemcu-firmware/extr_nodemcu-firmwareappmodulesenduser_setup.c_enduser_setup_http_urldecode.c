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
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 scalar_t__ isxdigit (char) ; 

__attribute__((used)) static int enduser_setup_http_urldecode(char *dst, const char *src, int src_len, int dst_len)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_http_urldecode");

  char *dst_start = dst;
  char *dst_last = dst + dst_len - 1; /* -1 to reserve space for last \0 */
  char a, b;
  int i;
  for (i = 0; i < src_len && *src && dst < dst_last; ++i)
  {
    if ((*src == '%') && ((a = src[1]) && (b = src[2])) && (isxdigit(a) && isxdigit(b)))
    {
      if (a >= 'a')
      {
        a -= 'a'-'A';
      }
      if (a >= 'A')
      {
        a -= ('A' - 10);
      }
      else
      {
        a -= '0';
      }
      if (b >= 'a')
      {
        b -= 'a'-'A';
      }
      if (b >= 'A')
      {
        b -= ('A' - 10);
      }
      else
      {
        b -= '0';
      }
      *dst++ = 16 * a + b;
      src += 3;
      i += 2;
    } else {
      char c = *src++;
      if (c == '+')
      {
        c = ' ';
      }
      *dst++ = c;
    }
  }
  *dst++ = '\0';
  return (i < src_len); /* did we fail to process all the input? */
}