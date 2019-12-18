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
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int LENGTH ; 
 int /*<<< orphan*/  MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 

char *MD5End(MD5_CTX *ctx, char *buf)
{
  int i;
  unsigned char digest[LENGTH];
  static const char hex[] = "0123456789abcdef";

  if (!buf)
    buf = malloc(2 * LENGTH + 1);
  if (!buf)
    return 0;
  MD5Final(digest, ctx);
  for (i = 0; i < LENGTH; i++) {
    buf[i + i] = hex[digest[i] >> 4];
    buf[i + i + 1] = hex[digest[i] & 0x0f];
  }
  buf[i + i] = '\0';
  return buf;
}