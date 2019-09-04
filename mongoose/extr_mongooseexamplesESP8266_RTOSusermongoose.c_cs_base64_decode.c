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
 unsigned char from_b64 (unsigned char const) ; 

int cs_base64_decode(const unsigned char *s, int len, char *dst, int *dec_len) {
  unsigned char a, b, c, d;
  int orig_len = len;
  char *orig_dst = dst;
  while (len >= 4 && (a = from_b64(s[0])) != 255 &&
         (b = from_b64(s[1])) != 255 && (c = from_b64(s[2])) != 255 &&
         (d = from_b64(s[3])) != 255) {
    s += 4;
    len -= 4;
    if (a == 200 || b == 200) break; /* '=' can't be there */
    *dst++ = a << 2 | b >> 4;
    if (c == 200) break;
    *dst++ = b << 4 | c >> 2;
    if (d == 200) break;
    *dst++ = c << 6 | d;
  }
  *dst = 0;
  if (dec_len != NULL) *dec_len = (dst - orig_dst);
  return orig_len - len;
}